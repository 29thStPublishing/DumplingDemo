//
//  NetworkManager.swift
//  DumplingDemo
//
//  Created by Lata Rastogi on 16/06/15.
//  Copyright (c) 2015 29th Street. All rights reserved.
//

import Foundation
import Dumpling2

class NetworkManager: AFHTTPRequestOperationManager {
    
    struct Singleton {
        static let sharedInstance = NetworkManager()
    }
    
    class var sharedInstance: NetworkManager {
        return Singleton.sharedInstance
    }
    
    override init(baseURL:NSURL) {
        super.init(baseURL: baseURL)
        self.requestSerializer = AFJSONRequestSerializer()
    }
    
    init() {
        var url = NSURL(string: "https://serial-subscriber.29.io/")
        super.init(baseURL: url)
    }
    
    required init(coder aDecoder: NSCoder) {
        super.init(coder: aDecoder)
    }
    
    func requestData(methodType: String, urlString:String, params: AnyObject?, completion:(data:AnyObject?, error:NSError?) -> ()) {
        
        self.requestSerializer = AFJSONRequestSerializer()
        
        let nonce = self.generateNonce()
        //MARK: This secret key will change
        var mainBundle = NSBundle.mainBundle()
        var secretKey: String = mainBundle.objectForInfoDictionaryKey("SharedSecret") as! String
        
        self.requestSerializer.setValue(nonce, forHTTPHeaderField: "X-Serial-Nonce")
        
        var parameters: NSString = NSString()
        if params != nil {
            if let jsonData = NSJSONSerialization.dataWithJSONObject(params!, options: NSJSONWritingOptions.allZeros, error: nil) {
                var jsonParams = NSString(data: jsonData, encoding: NSUTF8StringEncoding)
                parameters = jsonParams!
            }
        }
        let hashString = "\(nonce)\(secretKey)/\(urlString)\(parameters)"
        var hash = self.generateHash(hashString)
        self.requestSerializer.setValue(hash, forHTTPHeaderField: "X-Serial-MD5")
        
        if methodType == "GET" {
            
            var operation = self.GET(urlString,
                parameters: params,
                success: { (operation: AFHTTPRequestOperation!, responseObject: AnyObject!) in
                    completion(data: responseObject, error: nil)
                },
                failure: { (operation: AFHTTPRequestOperation!, error: NSError!) in
                    completion(data: nil, error: error)
            })
        }
        else if methodType == "POST" {
            
            var operation = self.POST(urlString,
                parameters: params,
                success: { (operation: AFHTTPRequestOperation!, responseObject: AnyObject!) in
                    completion(data: responseObject, error: nil)
                },
                failure: { (operation: AFHTTPRequestOperation!, error: NSError!) in
                    completion(data: nil, error: error)
            })
            
            if let nsdata = operation.request.HTTPBody {
                var dataStr = NSString(data: nsdata, encoding: NSUTF8StringEncoding)
                NSLog("\(dataStr),,,, \(operation.request)")
            }
        }
    }
    
    func requestSyncData(methodType: String, urlString:String, params: AnyObject?) -> AnyObject? {
        
        let nonce = self.generateNonce()
        var mainBundle = NSBundle.mainBundle()
        var secretKey: String = mainBundle.objectForInfoDictionaryKey("SharedSecret") as! String
        
        self.requestSerializer.setValue(nonce, forHTTPHeaderField: "X-Serial-Nonce")
        
        var parameters: NSString = NSString()
        if params != nil {
            if let jsonData = NSJSONSerialization.dataWithJSONObject(params!, options: NSJSONWritingOptions.allZeros, error: nil) {
                var jsonParams = NSString(data: jsonData, encoding: NSUTF8StringEncoding)
                parameters = jsonParams!
            }
        }
        let hashString = "\(nonce)\(secretKey)/\(urlString)\(parameters)"
        var hash = self.generateHash(hashString)
        self.requestSerializer.setValue(hash, forHTTPHeaderField: "X-Serial-MD5")
        
        var operation: AFHTTPRequestOperation
        if methodType == "GET" {
            operation = self.GET(urlString, parameters: params, success: nil, failure: nil)
        }
        else {
            
            operation = self.POST(urlString, parameters: params, success: nil, failure: nil)
        }
        
        operation.responseSerializer.acceptableContentTypes = NSSet(objects: "text/html", "application/json") as Set<NSObject>
        self.operationQueue.waitUntilAllOperationsAreFinished()
        
        NSRunLoop.currentRunLoop().runUntilDate(NSDate())
        
        if operation.error == nil {
            return operation.responseObject
        }
        return NSNumber(integer: operation.response.statusCode)
    }
    
    func generateNonce() -> String {
        let data = NSMutableData(length: 32)
        let result = SecRandomCopyBytes(kSecRandomDefault, 32, UnsafeMutablePointer<UInt8>(data!.mutableBytes))
        
        let base64str = data?.base64EncodedStringWithOptions(NSDataBase64EncodingOptions.Encoding64CharacterLineLength)
        return base64str!
    }
    
    func generateHash(string: String) -> String {
        let str = string.cStringUsingEncoding(NSUTF8StringEncoding)
        let strLen = CC_LONG(string.lengthOfBytesUsingEncoding(NSUTF8StringEncoding))
        let digestLen = Int(CC_MD5_DIGEST_LENGTH)
        let result = UnsafeMutablePointer<CUnsignedChar>.alloc(digestLen)
        
        CC_MD5(str!, strLen, result)
        var hash = NSMutableString()
        for i in 0..<digestLen {
            hash.appendFormat("%02x", result[i])
        }
        result.dealloc(digestLen)
        
        return String(format: hash as String)
    }
}