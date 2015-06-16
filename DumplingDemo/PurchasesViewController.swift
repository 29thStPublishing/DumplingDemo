//
//  PurchasesViewController.swift
//  DumplingDemo
//
//  Created by Lata Rastogi on 16/06/15.
//  Copyright (c) 2015 29th Street. All rights reserved.
//

import Foundation
import StoreKit
import Dumpling2

class PurchasesViewController: UITableViewController, SKProductsRequestDelegate {
    
    var objects = [AnyObject]()
    var accessControl: AccessControlDemo = AccessControlDemo()
    
    
    override func awakeFromNib() {
        super.awakeFromNib()
    }
    
    override func viewDidLoad() {
        super.viewDidLoad()
        
        NSNotificationCenter.defaultCenter().addObserver(self, selector: "updateArticleStatus:", name: "downloadComplete", object: nil)
        
        let restoreButton = UIBarButtonItem(barButtonSystemItem: UIBarButtonSystemItem.Refresh, target: self, action: "restorePurchases:")
        self.navigationItem.rightBarButtonItem = restoreButton
        
        SKPaymentQueue.defaultQueue().addTransactionObserver(accessControl)
        self.getProductInfo()
        
    }
    
    func restorePurchases(sender: AnyObject) {
        //MARK: Make this call to restore IAPs for logged in iTunes user
        //accessControl.restorePurchases(nil)
        
        //MARK: Make this call to get all SKUs purchased for this email id
        //accessControl.listPurchases("fluppywhumpus@gregario.com")
        
        //MARK: Make this call to sync all IAPs to server with this email id
        accessControl.syncPurchases("foo@fluffbundler.com")
    }
    
    func getProductInfo() {
        if SKPaymentQueue.canMakePayments() {
            //TODO: Replace the product ids with your IAP product id
            var set = NSSet(objects: "io.29.testmag.article.225", "io.29.testmag.article.226", "io.29.testmag.article.227", "io.29.testmag.article.228", "io.29.testmag.article.229") as Set<NSObject>
            var productsRequest = SKProductsRequest(productIdentifiers: set)
            productsRequest.delegate = self
            productsRequest.start()
        }
    }
    
    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }
    
    //MARK: SKProductsRequestDelegate
    func productsRequest(request: SKProductsRequest!, didReceiveResponse response: SKProductsResponse!) {
        
        var products: [SKProduct] = response.products as! [SKProduct]
        
        if (products.count > 0) {
            for product: SKProduct in products {
                objects.append(product)
            }
        }
        
        var invalidIds = response.invalidProductIdentifiers
        
        for product in invalidIds {
            println("Product not found: \(product)")
        }
        
        //Reload table
        self.tableView.reloadData()
    }
    
    // MARK: - Segues
    
    override func prepareForSegue(segue: UIStoryboardSegue, sender: AnyObject?) {
        if segue.identifier == "ShowPurchaseDetail" {
            if let indexPath = self.tableView.indexPathForSelectedRow() {
                let object: SKProduct = objects[indexPath.row] as! SKProduct
                (segue.destinationViewController as! PurchaseDetailViewController).detailItem = object.productIdentifier
            }
        }
    }
    
    // MARK: - Table View
    
    override func numberOfSectionsInTableView(tableView: UITableView) -> Int {
        return 1
    }
    
    override func tableView(tableView: UITableView, numberOfRowsInSection section: Int) -> Int {
        return objects.count
    }
    
    override func tableView(tableView: UITableView, cellForRowAtIndexPath indexPath: NSIndexPath) -> UITableViewCell {
        let cell = tableView.dequeueReusableCellWithIdentifier("Cell", forIndexPath: indexPath) as! UITableViewCell
        
        var product: SKProduct = objects[indexPath.row] as! SKProduct
        cell.textLabel!.text = product.localizedTitle
        return cell
    }
    
    override func tableView(tableView: UITableView, didSelectRowAtIndexPath indexPath: NSIndexPath) {
        var product: SKProduct = objects[indexPath.row] as! SKProduct
        
        var payment = SKPayment(product: product)
        SKPaymentQueue.defaultQueue().addPayment(payment)
    }
    
    //MARK: - Verification
    func updatePurchaseStatus(notif: NSNotification) {
        //Check if verification is complete or not
        var userInfo: [String: NSNumber] = notif.userInfo as! [String: NSNumber]
        if let indexPath = self.tableView.indexPathForSelectedRow() {
            let object: SKProduct = objects[indexPath.row] as! SKProduct
            let verified = userInfo[object.productIdentifier]
            if verified?.boolValue == true {
                self.performSegueWithIdentifier("ShowPurchaseDetail", sender: nil)
            }
        }
    }
    
    //MARK: - Notifications
    func updateArticleStatus(notif: NSNotification) {
        //Add article as purchase object
        var userInfo: [String : String] = notif.userInfo as! [String : String]
        let keys = (userInfo as NSDictionary).allKeys
        if keys.count > 0 {
            if let article: Article = Article.getArticle(keys[0] as? String, appleId: nil) {
                accessControl.purchaseItem(article)
            }
        }
    }
}

