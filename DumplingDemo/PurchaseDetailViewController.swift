//
//  PurchaseDetailViewController.swift
//  DumplingDemo
//
//  Created by Lata Rastogi on 16/06/15.
//  Copyright (c) 2015 29th Street. All rights reserved.
//

import Foundation
import Dumpling2

class PurchaseDetailViewController: UIViewController {
    
    @IBOutlet weak var detailDescriptionLabel: UILabel!
    var accessControl: AccessControlDemo = AccessControlDemo()
    
    var detailItem: AnyObject? {
        didSet {
            // Update the view.
            self.configureView()
        }
    }
    
    func configureView() {
        // Update the user interface for the detail item.
        if let detail: AnyObject = self.detailItem {
            if let label = self.detailDescriptionLabel {
                label.text = "Downloading article: \(detail.description)"
            }
        }
    }
    
    override func viewDidLoad() {
        super.viewDidLoad()
        // Do any additional setup after loading the view, typically from a nib.
        self.configureView()
        
        NSNotificationCenter.defaultCenter().addObserver(self, selector: "updateArticleStatus:", name: "downloadComplete", object: nil)
        
        accessControl.downloadArticle(self.detailItem as! String)
    }
    
    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }
    
    func updateArticleStatus(notif: NSNotification) {
        if let label = self.detailDescriptionLabel {
            label.text = "Article downloaded: \(self.detailItem)"
            
            //Add article as purchase object to database
            if let detail: String = self.detailItem as? String {
                if let article: Article = Article.getArticle(nil, appleId: detail) {
                    accessControl.purchaseItem(article)
                }
            }
        }
        NSNotificationCenter.defaultCenter().removeObserver(self)
    }
    
}

