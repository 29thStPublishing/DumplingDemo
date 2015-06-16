//
//  AccessControlDemo.swift
//  DumplingDemo
//
//  Created by Lata Rastogi on 16/06/15.
//  Copyright (c) 2015 29th Street. All rights reserved.
//

import Foundation
import Dumpling2
import StoreKit

class AccessControlDemo: NSObject, AccessControl, SKPaymentTransactionObserver {
    
    var purchaseHandler: PurchaseHandler?
    
    override init() {
        super.init()
        var docPaths = NSSearchPathForDirectoriesInDomains(NSSearchPathDirectory.DocumentDirectory, NSSearchPathDomainMask.UserDomainMask, true)
        var docsDir: NSString = docPaths[0] as! NSString
        
        self.purchaseHandler = PurchaseHandler(folder: docsDir)!
        
        NSNotificationCenter.defaultCenter().addObserver(self, selector: "updateArticleStatus:", name: "downloadComplete", object: nil)
    }
    
    ///Mark an item as purchased - add Purchase object to database
    func purchaseItem(object: AnyObject) {
        var globalId: String = ""
        var appleId: String = ""
        var type: String = ""
        
        if object.isKindOfClass(Volume) {
            globalId = (object as! Volume).globalId
            type = "volume"
        }
        else if object.isKindOfClass(Issue) {
            globalId = (object as! Issue).globalId
            appleId = (object as! Issue).appleId
            type = "issue"
        }
        else if object.isKindOfClass(Article) {
            globalId = (object as! Article).globalId
            appleId = (object as! Article).appleId
            type = "article"
        }
        var purchase = Purchase()
        purchase.appleId = appleId
        purchase.globalId = globalId
        purchase.mode = "IAP"
        purchase.type = type
        
        self.purchaseHandler!.addPurchase(purchase)
    }
    
    ///Restore IAPs for current logged in user - also downloads the articles
    ///If user id is not-nil, will retrieve user's web purchases and download those as well
    func restorePurchases(userId: AnyObject?) {
        SKPaymentQueue.defaultQueue().addTransactionObserver(self)
        
        if (SKPaymentQueue.canMakePayments()) {
            SKPaymentQueue.defaultQueue().restoreCompletedTransactions()
        }
        
        if let userIdentity: AnyObject = userId {
            self.restoreWebPurchases(userIdentity)
        }
    }
    
    ///Restore purchases made on the web with this email id
    func restoreWebPurchases(userId: AnyObject) {
        var networkManager = NetworkManager.sharedInstance
        
        let requestURL = "api/1.5/serial/email?email=\(userId)"
        
        if let data: AnyObject = networkManager.requestSyncData("GET", urlString: requestURL, params: nil) {
            if data.isKindOfClass(NSNumber) {
                NSLog("Error retrieving data: \(data.intValue)")
            }
            else {
                var response: Array<String> = data as! Array<String>
                if response.count > 0 {
                    //Get all SKUs, add their articles to the database and register Purchase
                    for sku: String in response {
                        self.downloadArticle(sku)
                    }
                }
            }
        }
    }
    
    ///Check if the SKU is available for this user or not
    func isAvailable(appleId: String, userId: AnyObject?) -> Bool {
        //If user id is available, send to server and get
        if let purchaseSKUs = self.listPurchases(userId) {
            if contains(purchaseSKUs, appleId) {
                return true
            }
        }
        return false
    }
    
    ///Get all an array of SKUs that the user has access to (through IAP or web purchase)
    func listPurchases(userId: AnyObject?) -> Array<String>? {
        
        var purchases: Array<String> = []
        if let array = self.purchaseHandler!.getPurchases(nil) {
            for purchase: Purchase in array {
                purchases.append(purchase.appleId)
            }
        }
        
        if let email: String = userId as? String {
            var networkManager = NetworkManager.sharedInstance
            
            let requestURL = "api/1.5/serial/email?email=\(email)"
            
            if let data: AnyObject = networkManager.requestSyncData("GET", urlString: requestURL, params: nil) {
                if data.isKindOfClass(NSNumber) {
                    //Error message
                    NSLog("Error retrieving data: \(data.intValue)")
                }
                else {
                    var response: Array<String> = data as! Array<String>
                    if response.count > 0 {
                        //Get all SKUs
                        for sku: String in response {
                            purchases.append(sku)
                        }
                    }
                }
            }
        }
        
        return purchases
    }
    
    ///Save all purchases in local database to the server - with user email
    func syncPurchases(userId: AnyObject) {
        //Sync all IAPs with server - send receipt
        var receiptURL = NSBundle.mainBundle().appStoreReceiptURL
        var receipt: NSData = NSData(contentsOfURL:receiptURL!, options: nil, error: nil)!
        
        var receiptData: NSString = receipt.base64EncodedStringWithOptions(NSDataBase64EncodingOptions(rawValue: 0))
        let encodedReceiptData: String = self.urlEncodeString(receiptData)
        
        var requestURL = "api/1.5/serial/receipts?receipt=\(encodedReceiptData)"
        
        var networkManager = NetworkManager.sharedInstance
        if let data: AnyObject = networkManager.requestSyncData("POST", urlString: requestURL, params: nil) {
            if data.isKindOfClass(NSNumber) {
                NSLog("Error saving data: \(data.intValue)")
            }
            else {
                var response: Array<String> = data as! Array<String>
                if response.count > 0 {
                    //Send all SKUs with the email id to the server for syncing
                    var params = NSMutableDictionary()
                    params.setObject(userId, forKey: "email")
                    params.setObject(response, forKey: "SKUs")
                    params.setObject("true", forKey: "free")
                    
                    requestURL = "api/1.5/serial/email"
                    
                    networkManager.requestData("POST", urlString: requestURL, params: params) {
                        (data:AnyObject?, error:NSError?) -> () in
                        if let err = error {
                            NSLog("ADDED: \(data)")
                        }
                        else if let err = error {
                            println("Error: " + err.description)
                        }
                    }
                }
            }
        }
        
    }
    
    
    //MARK: SKPaymentTransactionObserver
    
    @objc func paymentQueue(queue: SKPaymentQueue!, updatedTransactions transactions: [AnyObject]!) {
        
        for transaction in transactions as! [SKPaymentTransaction] {
            
            switch transaction.transactionState {
                
            case SKPaymentTransactionState.Purchased:
                //Download content and add to DB
                self.verifyAndUnlockFeature(transaction)
                SKPaymentQueue.defaultQueue().finishTransaction(transaction)
                
            case SKPaymentTransactionState.Restored:
                SKPaymentQueue.defaultQueue().finishTransaction(transaction)
                self.downloadArticle(transaction.payment.productIdentifier)
                
            case SKPaymentTransactionState.Failed:
                SKPaymentQueue.defaultQueue().finishTransaction(transaction)
                NSLog("ERROR: \(transaction.error)")
                var userInfoDict = NSDictionary(object: NSNumber(bool: false), forKey: transaction.payment.productIdentifier)
                NSNotificationCenter.defaultCenter().postNotificationName("verification", object: nil, userInfo: userInfoDict as! Dictionary<String, NSNumber>)
                
            default:
                break
            }
        }
    }
    
    //MARK: - Validation
    func verifyAndUnlockFeature(transaction: SKPaymentTransaction) {
        var receiptURL = NSBundle.mainBundle().appStoreReceiptURL
        var receipt: NSData = NSData(contentsOfURL:receiptURL!, options: nil, error: nil)!
        
        var receiptData: NSString = receipt.base64EncodedStringWithOptions(NSDataBase64EncodingOptions(rawValue: 0))
        let encodedReceiptData: String = self.urlEncodeString(receiptData)
        
        let requestURL = "api/1.5/serial/receipts?receipt=\(encodedReceiptData)"
        
        var networkManager = NetworkManager.sharedInstance
        
        networkManager.requestData("POST", urlString: requestURL, params: nil) {
            (data:AnyObject?, error:NSError?) -> () in
            if data != nil {
                var userInfoDict = NSDictionary(object: NSNumber(bool: true), forKey: transaction.payment.productIdentifier)
                NSNotificationCenter.defaultCenter().postNotificationName("verification", object: nil, userInfo: userInfoDict as! Dictionary<String, NSNumber>)
            }
            else if let err = error {
                println("Error: " + err.description)
                //Don't unlock the content
                var userInfoDict = NSDictionary(object: NSNumber(bool: false), forKey: transaction.payment.productIdentifier)
                NSNotificationCenter.defaultCenter().postNotificationName("verification", object: nil, userInfo: userInfoDict as! Dictionary<String, NSNumber>)
            }
        }
    }
    
    //MARK: - Download
    func downloadArticle(appleId: String) {
        
        var docPaths = NSSearchPathForDirectoriesInDomains(NSSearchPathDirectory.DocumentDirectory, NSSearchPathDomainMask.UserDomainMask, true)
        var docsDir: NSString = docPaths[0] as! NSString
        
        if let articleHandler = ArticleHandler(folder: docsDir) {
            articleHandler.addArticleWith(appleId)
        }
    }
    
    //MARK: - Notification
    func updateArticleStatus(notif: NSNotification) {
        //Get articleId of the downloaded article and add Purchase
        var userInfo: [String : String] = notif.userInfo as! [String : String]
        let keys = (userInfo as NSDictionary).allKeys
        if keys.count > 0 {
            if let article: Article = Article.getArticle(keys[0] as? String, appleId: nil) {
                self.purchaseItem(article)
            }
        }
    }
    
    //MARK: - Test
    func urlEncodeString(str: NSString) -> String {
        
        var raw: NSString = str
        var result: CFString = CFURLCreateStringByAddingPercentEscapes(kCFAllocatorDefault, str, "[].",":/?&=;+!@#$()',*",CFStringConvertNSStringEncodingToEncoding(NSUTF8StringEncoding))
        
        var swiftStr: String = (result as NSString) as String
        
        return swiftStr
    }
}
