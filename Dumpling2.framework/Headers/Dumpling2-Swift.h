// Generated by Apple Swift version 1.2 (swiftlang-602.0.49.3 clang-clang-602.0.49)
#pragma clang diagnostic push

#if defined(__has_include) && __has_include(<swift/objc-prologue.h>)
# include <swift/objc-prologue.h>
#endif

#pragma clang diagnostic ignored "-Wauto-import"
#include <objc/NSObject.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

#if defined(__has_include) && __has_include(<uchar.h>)
# include <uchar.h>
#elif !defined(__cplusplus) || __cplusplus < 201103L
typedef uint_least16_t char16_t;
typedef uint_least32_t char32_t;
#endif

typedef struct _NSZone NSZone;

#if !defined(SWIFT_PASTE)
# define SWIFT_PASTE_HELPER(x, y) x##y
# define SWIFT_PASTE(x, y) SWIFT_PASTE_HELPER(x, y)
#endif
#if !defined(SWIFT_METATYPE)
# define SWIFT_METATYPE(X) Class
#endif

#if defined(__has_attribute) && __has_attribute(objc_runtime_name)
# define SWIFT_RUNTIME_NAME(X) __attribute__((objc_runtime_name(X)))
#else
# define SWIFT_RUNTIME_NAME(X)
#endif
#if !defined(SWIFT_CLASS_EXTRA)
# define SWIFT_CLASS_EXTRA
#endif
#if !defined(SWIFT_PROTOCOL_EXTRA)
# define SWIFT_PROTOCOL_EXTRA
#endif
#if !defined(SWIFT_ENUM_EXTRA)
# define SWIFT_ENUM_EXTRA
#endif
#if !defined(SWIFT_CLASS)
# if defined(__has_attribute) && __has_attribute(objc_subclassing_restricted) 
#  define SWIFT_CLASS(SWIFT_NAME) SWIFT_RUNTIME_NAME(SWIFT_NAME) __attribute__((objc_subclassing_restricted)) SWIFT_CLASS_EXTRA
# else
#  define SWIFT_CLASS(SWIFT_NAME) SWIFT_RUNTIME_NAME(SWIFT_NAME) SWIFT_CLASS_EXTRA
# endif
#endif

#if !defined(SWIFT_PROTOCOL)
# define SWIFT_PROTOCOL(SWIFT_NAME) SWIFT_RUNTIME_NAME(SWIFT_NAME) SWIFT_PROTOCOL_EXTRA
#endif

#if !defined(SWIFT_EXTENSION)
# define SWIFT_EXTENSION(M) SWIFT_PASTE(M##_Swift_, __LINE__)
#endif

#if !defined(OBJC_DESIGNATED_INITIALIZER)
# if defined(__has_attribute) && __has_attribute(objc_designated_initializer)
#  define OBJC_DESIGNATED_INITIALIZER __attribute__((objc_designated_initializer))
# else
#  define OBJC_DESIGNATED_INITIALIZER
# endif
#endif
#if !defined(SWIFT_ENUM)
# define SWIFT_ENUM(_type, _name) enum _name : _type _name; enum SWIFT_ENUM_EXTRA _name : _type
#endif
#if __has_feature(nullability)
#  define SWIFT_NULLABILITY(X) X
#else
# if !defined(__nonnull)
#  define __nonnull
# endif
# if !defined(__nullable)
#  define __nullable
# endif
# if !defined(__null_unspecified)
#  define __null_unspecified
# endif
#  define SWIFT_NULLABILITY(X)
#endif
#if defined(__has_feature) && __has_feature(modules)
@import ObjectiveC;
#endif

#import <Dumpling2/Dumpling2.h>

#pragma clang diagnostic ignored "-Wproperty-attribute-mismatch"
#pragma clang diagnostic ignored "-Wduplicate-method-arg"
@class NSDate;
@class NSString;


/// A model object for Articles 
SWIFT_CLASS("_TtC9Dumpling27Article")
@interface Article : RLMObject

/// Global id of an article - this is unique for each article
@property (nonatomic, copy) NSString * __nonnull globalId;

/// Article title
@property (nonatomic, copy) NSString * __nonnull title;

/// Article description
@property (nonatomic, copy) NSString * __nonnull articleDesc;
@property (nonatomic, copy) NSString * __nonnull slug;
@property (nonatomic, copy) NSString * __nonnull dek;

/// Article content
@property (nonatomic, copy) NSString * __nonnull body;

/// Permanent link to the article
@property (nonatomic, copy) NSString * __nonnull permalink;

/// Article URL
@property (nonatomic, copy) NSString * __nonnull url;

/// URL to the article's source
@property (nonatomic, copy) NSString * __nonnull sourceURL;

/// Article author's name
@property (nonatomic, copy) NSString * __nonnull authorName;

/// Link to the article author's profile
@property (nonatomic, copy) NSString * __nonnull authorURL;

/// Section under which the article falls
@property (nonatomic, copy) NSString * __nonnull section;

/// Type of article
@property (nonatomic, copy) NSString * __nonnull articleType;

/// Keywords which the article falls under
@property (nonatomic, copy) NSString * __nonnull keywords;

/// Article commentary
@property (nonatomic, copy) NSString * __nonnull commentary;

/// Article published date
@property (nonatomic) NSDate * __nonnull date;

/// Article metadata
@property (nonatomic, copy) NSString * __nonnull metadata;
@property (nonatomic, copy) NSString * __nonnull versionStashed;

/// Placement of the article in an issue
@property (nonatomic) NSInteger placement;

/// URL for the article's feature image
@property (nonatomic, copy) NSString * __nonnull mainImageURL;

/// URL for the article's thumbnail image
@property (nonatomic, copy) NSString * __nonnull thumbImageURL;

/// Status of article (published or not)
@property (nonatomic) BOOL isPublished;

/// Whether the article is featured for the given issue or not
@property (nonatomic) BOOL isFeatured;
+ (NSString * __nonnull)primaryKey;

/// This method accepts an issue's global id and deletes all articles from the database which belong to that issue
///
/// <dl><dt>brief</dt><dd><p>Delete articles and assets for a specific issue</p></dd></dl>
/// \param issueId The global id of the issue whose articles have to be deleted
+ (void)deleteArticlesFor:(NSString * __nonnull)issueId;

/// This method accepts an issue's global id, type of article to be found and type of article to be excluded. It retrieves all articles which meet these conditions and returns them in an array.
///
/// All parameters are optional. At least one of the parameters is needed when making this call. The parameters follow AND conditions
///
/// <dl><dt>brief</dt><dd><p>Get all articles fulfiling certain conditions</p></dd></dl>
/// <dl><dt>return</dt><dd><p>an array of articles fulfiling the conditions</p></dd></dl>
/// \param issueId The global id of the issue whose articles have to be searched
///
/// \param type The article type which should be searched and returned
///
/// \param excludeType The article type which should not be included in the search
///
/// \param count Number of articles to be returned
///
/// \param page Page number (will be used with count)
+ (NSArray * __nullable)getArticlesFor:(NSString * __nullable)issueId type:(NSString * __nullable)type excludeType:(NSString * __nullable)excludeType count:(NSInteger)count page:(NSInteger)page;

/// This method accepts an issue's global id and the key and value for article search. It retrieves all articles which meet these conditions and returns them in an array.
///
/// The key and value are needed. Other articles are optional. To ignore pagination, pass the count as 0
///
/// <dl><dt>return</dt><dd><p>an array of articles fulfiling the conditions</p></dd></dl>
/// \param issueId The global id of the issue whose articles have to be searched
///
/// \param key The key whose values need to be searched. Please ensure this has the same name as the properties available. The value can be any of the Article properties, keywords or customMeta keys
///
/// \param value The value of the key for the articles to be retrieved
///
/// \param count Number of articles to be returned
///
/// \param page Page number (will be used with count)
+ (NSArray * __nullable)getArticlesFor:(NSString * __nullable)issueId key:(NSString * __nonnull)key value:(NSString * __nonnull)value count:(NSInteger)count page:(NSInteger)page;

/// This method inputs the global id or Apple id of an article and returns the Article object
///
/// <dl><dt>return</dt><dd><p>article object for the global/Apple id. Returns nil if the article is not found</p></dd></dl>
/// \param articleId The global id for the article
///
/// \param appleId The apple id/SKU for the article
+ (Article * __nullable)getArticle:(NSString * __nullable)articleId appleId:(NSString * __nullable)appleId;

/// This method accepts an issue's global id and returns all articles for an issue (or if nil, all issues) with specific keywords
///
/// <dl><dt>brief</dt><dd><p>Get all articles for an issue with specific keywords</p></dd></dl>
/// <dl><dt>return</dt><dd><p>an array of articles fulfiling the conditions</p></dd></dl>
/// \param keywords An array of String values with keywords that the article should have. If any of the keywords match, the article will be selected
///
/// \param issueId Global id for the issue which the articles must belong to. This parameter is optional
+ (NSArray * __nullable)searchArticlesWith:(NSArray * __nonnull)keywords issueId:(NSString * __nullable)issueId;

/// This method accepts an issue's global id and returns all articles for the issue which are featured
///
/// <dl><dt>brief</dt><dd><p>Get all  featured articles for a specific issue</p></dd></dl>
/// <dl><dt>return</dt><dd><p>an array of featured articles for the issue</p></dd></dl>
/// \param issueId Global id for the issue whose featured articles are needed
+ (NSArray * __nullable)getFeaturedArticlesFor:(NSString * __nonnull)issueId;

/// This method accepts a regular expression which should be used to identify placeholders for assets in an article body.
/// The default asset pattern is <code><!-- \\[ASSET: .+\\] --></code>
///
/// <dl><dt>brief</dt><dd><p>Change the asset pattern</p></dd></dl>
/// \param newPattern The regex to identify pattern for asset placeholders
+ (void)setAssetPattern:(NSString * __nonnull)newPattern;

/// This method can be called on an Article object to save it back to the database
///
/// <dl><dt>brief</dt><dd><p>Save an Article to the database</p></dd></dl>
- (void)saveArticle;

/// This method replaces the asset placeholders in the body of the Article with actual assets using HTML codes
/// Images are replaced with HTML img tags, Audio and Video with HTML audio and video tags respectively
///
/// <dl><dt>brief</dt><dd><p>Replace asset pattern with actual assets in an Article body</p></dd></dl>
/// <dl><dt>return</dt><dd><p>HTML body of the article with actual assets in place of placeholders</p></dd></dl>
- (NSString * __nonnull)replacePatternsWithAssets;

/// This method returns all articles for an issue whose publish date is newer than the published date of current article
///
/// <dl><dt>brief</dt><dd><p>Get all articles newer than a specific article</p></dd></dl>
/// <dl><dt>return</dt><dd><p>an array of articles newer than the current article (in the same issue)</p></dd></dl>
- (NSArray * __nullable)getNewerArticles;

/// This method returns all articles for an issue whose publish date is before the published date of current article
///
/// <dl><dt>brief</dt><dd><p>Get all articles older than a specific article</p></dd></dl>
/// <dl><dt>return</dt><dd><p>an array of articles older than the current article (in the same issue)</p></dd></dl>
- (NSArray * __nullable)getOlderArticles;

/// This method returns the value for a specific key from the custom metadata of the article
///
/// <dl><dt>brief</dt><dd><p>Get value for a specific key from custom meta of an article</p></dd></dl>
/// <dl><dt>return</dt><dd><p>an object for the key from the custom metadata (or nil)</p></dd></dl>
- (id __nullable)getValue:(NSString * __nonnull)key;
- (SWIFT_NULLABILITY(null_unspecified) instancetype)init OBJC_DESIGNATED_INITIALIZER;
- (SWIFT_NULLABILITY(null_unspecified) instancetype)initWithObject:(id __null_unspecified)object OBJC_DESIGNATED_INITIALIZER;
@end



/// Starter class which adds independent articles to the database 
SWIFT_CLASS("_TtC9Dumpling214ArticleHandler")
@interface ArticleHandler : NSObject

/// Initializes the ArticleHandler with the given folder. This is where the database and assets will be saved. The method expects to find a key <code>ClientKey</code> in the project's Info.plist with your client key. If none is found, the method returns a nil
///
/// \param folder The folder where the database and downloaded assets should be saved
- (SWIFT_NULLABILITY(nullable) instancetype)initWithFolder:(NSString * __nonnull)folder OBJC_DESIGNATED_INITIALIZER;

/// Initializes the ArticleHandler with the Documents directory. This is where the database and assets will be saved. The API key is used for making calls to the Magnet API
///
/// \param clientkey Client API key to be used for making calls to the Magnet API
- (SWIFT_NULLABILITY(nonnull) instancetype)initWithClientkey:(NSString * __nonnull)clientkey OBJC_DESIGNATED_INITIALIZER;

/// Initializes the ArticleHandler with a custom directory. This is where the database and assets will be saved. The API key is used for making calls to the Magnet API
///
/// \param folder The folder where the database and downloaded assets should be saved
///
/// \param clientkey Client API key to be used for making calls to the Magnet API
- (SWIFT_NULLABILITY(nonnull) instancetype)initWithFolder:(NSString * __nonnull)folder clientkey:(NSString * __nonnull)clientkey OBJC_DESIGNATED_INITIALIZER;

/// The method uses the global id of an article, gets its content from the Magnet API and adds it to the database
///
/// <dl><dt>brief</dt><dd><p>Get Article details from API and add to database</p></dd></dl>
/// \param globalId The global id for the article
- (void)addArticleFromAPI:(NSString * __nonnull)globalId;
- (void)addAllArticles;

/// Get paginated articles (array) from the database
///
/// <dl><dt>return</dt><dd><p>Array of independent articles (without any issueIds)</p></dd></dl>
/// \param page Page number for results (starts at 0)
///
/// \param count Number of items to be returned (specify as 0 if you need all articles)
- (NSArray * __nullable)getAllArticles:(NSInteger)page count:(NSInteger)count;
@end

@class Issue;


/// A model object for Assets 
SWIFT_CLASS("_TtC9Dumpling25Asset")
@interface Asset : RLMObject

/// Global id of an asset - this is unique for each asset
@property (nonatomic, copy) NSString * __nonnull globalId;

/// Caption for the asset - used in the final rendered HTML
@property (nonatomic, copy) NSString * __nonnull caption;

/// Source attribution for the asset
@property (nonatomic, copy) NSString * __nonnull source;

/// File URL for the asset's square thumbnail
@property (nonatomic, copy) NSString * __nonnull squareURL;

/// File URL for the original asset
@property (nonatomic, copy) NSString * __nonnull originalURL;

/// File URL for the portrait image of the asset
@property (nonatomic, copy) NSString * __nonnull mainPortraitURL;

/// File URL for the landscape image of the asset
@property (nonatomic, copy) NSString * __nonnull mainLandscapeURL;

/// File URL for the icon image
@property (nonatomic, copy) NSString * __nonnull iconURL;

/// Custom metadata for the asset
@property (nonatomic, copy) NSString * __nonnull metadata;

/// Asset type. Defaults to a photo. Can be image, sound, video or custom
@property (nonatomic, copy) NSString * __nonnull type;

/// Placement of an asset for an article or issue
@property (nonatomic) NSInteger placement;

/// Folder which stores the asset files - downloaded or unzipped
@property (nonatomic, copy) NSString * __nonnull fullFolderPath;

/// Global id for the article with which the asset is associated. Can be blank if this is an issue's asset
@property (nonatomic, copy) NSString * __nonnull articleId;

/// Issue object for the issue with which the asset is associated. Can be a default Issue object if the asset is for an independent article
@property (nonatomic) Issue * __null_unspecified issue;

/// Global id of volume the asset is associated with. Can be blank if this is an issue or article asset
@property (nonatomic, copy) NSString * __nonnull volumeId;
+ (NSString * __nonnull)primaryKey;

/// This method lets you save an Asset object back to the database in case some changes are made to it
///
/// <dl><dt>brief</dt><dd><p>Save an Asset to the database</p></dd></dl>
- (void)saveAsset;

/// This method accepts the global id of an asset and deletes it from the database. The file for the asset is also deleted
///
/// <dl><dt>brief</dt><dd><p>Delete a specific asset</p></dd></dl>
/// \param assetId The global id for the asset
+ (void)deleteAsset:(NSString * __nonnull)assetId;

/// This method uses the global id for an issue and/or article and returns its first image asset (i.e. placement = 1, type = image)
///
/// <dl><dt>brief</dt><dd><p>Retrieve first asset for an issue/article</p></dd></dl>
/// <dl><dt>return</dt><dd><p>Asset object</p></dd></dl>
/// \param issueId The global id for the issue
///
/// \param articleId The global id for the article
///
/// \param volumeId The global id for the volume
+ (Asset * __nullable)getFirstAssetFor:(NSString * __nonnull)issueId articleId:(NSString * __nonnull)articleId volumeId:(NSString * __nullable)volumeId;

/// This method uses the global id for an issue and/or article and returns the number of assets it has
///
/// <dl><dt>brief</dt><dd><p>Retrieve number of assets for an issue/article</p></dd></dl>
/// <dl><dt>return</dt><dd><p>asset count for the issue and/or article</p></dd></dl>
/// \param issueId The global id for the issue
///
/// \param articleId The global id for the article
///
/// \param volumeId The global id of the volume
+ (NSUInteger)getNumberOfAssetsFor:(NSString * __nonnull)issueId articleId:(NSString * __nonnull)articleId volumeId:(NSString * __nullable)volumeId;

/// This method uses the global id for an issue and/or article and the assets in an array. It takes in an optional type parameter. If specified, only assets of that type will be returned
///
/// <dl><dt>brief</dt><dd><p>Retrieve all assets for an issue/article of a specific type</p></dd></dl>
/// <dl><dt>return</dt><dd><p>array of assets following the conditions</p></dd></dl>
/// \param issueId The global id for the issue
///
/// \param articleId The global id for the article
///
/// \param volumeId The global id for the volume
///
/// \param type The type of asset. If nil, all assets will be returned
+ (NSArray * __nullable)getAssetsFor:(NSString * __nonnull)issueId articleId:(NSString * __nonnull)articleId volumeId:(NSString * __nullable)volumeId type:(NSString * __nullable)type;

/// This method inputs the global id of an asset and returns the Asset object
///
/// <dl><dt>brief</dt><dd><p>Retrieve a specific asset</p></dd></dl>
/// <dl><dt>return</dt><dd><p>asset object for the global id. Returns nil if the asset is not found</p></dd></dl>
/// \param assetId The global id for the asset
+ (Asset * __nullable)getAsset:(NSString * __nonnull)assetId;

/// This method inputs the global id of an issue and/or article and returns all sound assets for it in an array
///
/// <dl><dt>brief</dt><dd><p>Retrieve all sound files for an article/issue as a playlist/array</p></dd></dl>
/// <dl><dt>return</dt><dd><p>Array of sound asset objects for the given issue and/or article</p></dd></dl>
/// \param issueId The global id for the issue
///
/// \param articleId The global id for the article
+ (NSArray * __nullable)getPlaylistFor:(NSString * __nonnull)issueId articleId:(NSString * __nonnull)articleId;

/// This method returns the path of the asset file for the current object
///
/// <dl><dt>return</dt><dd><p>Path of the asset file or nil if not found</p></dd></dl>
- (NSString * __nullable)getAssetPath;
- (SWIFT_NULLABILITY(null_unspecified) instancetype)init OBJC_DESIGNATED_INITIALIZER;
- (SWIFT_NULLABILITY(null_unspecified) instancetype)initWithObject:(id __null_unspecified)object OBJC_DESIGNATED_INITIALIZER;
@end



/// A model object for Issue 
SWIFT_CLASS("_TtC9Dumpling25Issue")
@interface Issue : RLMObject

/// Global id of an issue - this is unique for each issue
@property (nonatomic, copy) NSString * __nonnull globalId;

/// Title of the issue
@property (nonatomic, copy) NSString * __nonnull title;

/// Description of the issue
@property (nonatomic, copy) NSString * __nonnull issueDesc;

/// Folder saving all the assets for the issue
@property (nonatomic, copy) NSString * __nonnull assetFolder;

/// Global id of the asset which is the cover image of the issue
@property (nonatomic, copy) NSString * __nonnull coverImageId;

/// File URL for the icon image
@property (nonatomic, copy) NSString * __nonnull iconImageURL;

/// Published date for the issue
@property (nonatomic) NSDate * __nonnull publishedDate;

/// Last updated date for the issue
@property (nonatomic, copy) NSString * __nonnull lastUpdateDate;

/// Display date for an issue
@property (nonatomic, copy) NSString * __nonnull displayDate;

/// Custom metadata of the issue
@property (nonatomic, copy) NSString * __nonnull metadata;
+ (NSString * __nonnull)primaryKey;

/// This method uses the SKU/Apple id for an issue and deletes it from the database. All the issue's articles, assets, article assets are deleted from the database and the file system
///
/// <dl><dt>brief</dt><dd><p>Delete an issue</p></dd></dl>
/// \param appleId The SKU/Apple id for the issue
+ (void)deleteIssue:(NSString * __nonnull)appleId;

/// This method returns the Issue object for the most recent issue in the database (sorted by publish date)
///
/// <dl><dt>brief</dt><dd><p>Find most recent issue</p></dd></dl>
/// <dl><dt>return</dt><dd><p>Object for most recent issue</p></dd></dl>
+ (Issue * __nullable)getNewestIssue;

/// This method takes in an SKU/Apple id and returns the Issue object associated with it (or nil if not found in the database)
///
/// <dl><dt>brief</dt><dd><p>Get the issue for a specific Apple id</p></dd></dl>
/// <dl><dt>return</dt><dd><p>Issue object for the given SKU/Apple id</p></dd></dl>
/// \param appleId The SKU/Apple id to search for
+ (Issue * __nullable)getIssueFor:(NSString * __nonnull)appleId;

/// This method returns all issues for a given volume or if volumeId is nil, all issues
///
/// <dl><dt>return</dt><dd><p>an array of issues for given volume or all issues if volumeId is nil</p></dd></dl>
/// \param volumeId Global id of the volume whose issues have to be retrieved
+ (NSArray * __nullable)getIssues:(NSString * __nullable)volumeId;

/// This method inputs the global id of an issue and returns the Issue object
///
/// <dl><dt>return</dt><dd><p>issue object for the global id. Returns nil if the issue is not found</p></dd></dl>
/// \param issueId The global id for the issue
+ (Issue * __nullable)getIssue:(NSString * __nonnull)issueId;

/// This method saves an issue back to the database
///
/// <dl><dt>brief</dt><dd><p>Save an Issue to the database</p></dd></dl>
- (void)saveIssue;

/// This method returns the value for a specific key from the custom metadata of the issue
///
/// <dl><dt>brief</dt><dd><p>Get value for a specific key from custom meta of an issue</p></dd></dl>
/// <dl><dt>return</dt><dd><p>an object for the key from the custom metadata (or nil)</p></dd></dl>
- (id __nullable)getValue:(NSString * __nonnull)key;

/// This method returns all issues whose publish date is older than the published date of current issue
///
/// <dl><dt>brief</dt><dd><p>Get all issues older than a specific issue</p></dd></dl>
/// <dl><dt>return</dt><dd><p>an array of issues older than the current issue</p></dd></dl>
- (NSArray * __nullable)getOlderIssues;

/// This method returns all issues whose publish date is newer than the published date of current issue
///
/// <dl><dt>brief</dt><dd><p>Get all issues newer than a specific issue</p></dd></dl>
/// <dl><dt>return</dt><dd><p>an array of issues newer than the current issue</p></dd></dl>
- (NSArray * __nullable)getNewerIssues;
- (SWIFT_NULLABILITY(null_unspecified) instancetype)init OBJC_DESIGNATED_INITIALIZER;
- (SWIFT_NULLABILITY(null_unspecified) instancetype)initWithObject:(id __null_unspecified)object OBJC_DESIGNATED_INITIALIZER;
@end

@class NSArray;


/// Starter class which adds issues to the database 
SWIFT_CLASS("_TtC9Dumpling212IssueHandler")
@interface IssueHandler : NSObject

/// Initializes the IssueHandler with the given folder. This is where the database and assets will be saved. The method expects to find a key <code>ClientKey</code> in the project's Info.plist with your client key. If none is found, the method returns a nil
///
/// <dl><dt>brief</dt><dd><p>Initializer object</p></dd></dl>
/// \param folder The folder where the database and downloaded assets should be saved
- (SWIFT_NULLABILITY(nullable) instancetype)initWithFolder:(NSString * __nonnull)folder OBJC_DESIGNATED_INITIALIZER;

/// Initializes the IssueHandler with the Documents directory. This is where the database and assets will be saved. The API key is used for making calls to the Magnet API
///
/// <dl><dt>brief</dt><dd><p>Initializer object</p></dd></dl>
/// \param clientkey Client API key to be used for making calls to the Magnet API
- (SWIFT_NULLABILITY(nonnull) instancetype)initWithClientkey:(NSString * __nonnull)clientkey OBJC_DESIGNATED_INITIALIZER;

/// Initializes the IssueHandler with a custom directory. This is where the database and assets will be saved. The API key is used for making calls to the Magnet API
///
/// <dl><dt>brief</dt><dd><p>Initializer object</p></dd></dl>
/// \param folder The folder where the database and downloaded assets should be saved
///
/// \param clientkey Client API key to be used for making calls to the Magnet API
- (SWIFT_NULLABILITY(nonnull) instancetype)initWithFolder:(NSString * __nonnull)folder clientkey:(NSString * __nonnull)clientkey OBJC_DESIGNATED_INITIALIZER;

/// The method uses an Apple id, gets a zip file from the project Bundle with the name appleId.zip, extracts its contents and adds the issue, articles and assets to the database
///
/// <dl><dt>brief</dt><dd><p>Add issue details from an extracted zip file to the database</p></dd></dl>
/// \param appleId The SKU/Apple id for the issue. The method looks for a zip with the same name in the Bundle
- (void)addIssueZip:(NSString * __nonnull)appleId;

/// The method uses the global id of an issue, gets its content from the Magnet API and adds it to the database
///
/// <dl><dt>brief</dt><dd><p>Get Issue details from API and add to database</p></dd></dl>
/// \param appleId The SKU/Apple id for the issue. The method looks for a zip with the same name in the Bundle
- (void)addIssueFromAPI:(NSString * __nonnull)issueId volumeId:(NSString * __nullable)volumeId;

/// The method is for testing only. It prints the available issues for a client api key
- (void)listIssues;

/// The method searches for an issue with a specific Apple ID. If the issue is not available in the database, the issue will be downloaded from the Magnet API and added to the DB
///
/// <dl><dt>brief</dt><dd><p>Search for an issue with an apple id</p></dd></dl>
/// <dl><dt>return</dt><dd><p>Issue object or nil if the issue is not in the database or on the server</p></dd></dl>
/// \param appleId The SKU/Apple id for the issue
- (Issue * __nullable)searchIssueFor:(NSString * __nonnull)appleId;

/// Get issue details from database for a specific global id
///
/// <dl><dt>return</dt><dd><p>Issue object or nil if the issue is not in the database</p></dd></dl>
/// \param issueId global id of the issue
- (Issue * __nullable)getIssue:(NSString * __nonnull)issueId;

/// Add an issue on Newsstand
///
/// \param issueId global id of the issue
- (void)addIssueOnNewsstand:(NSString * __nonnull)issueId;

/// Find download % progress for an issue or volume. The method requires either a volume's global id or an issue's global id. The issue's global id should be used only if it is an independent issue (i.e. not belonging to any volume)
///
/// <dl><dt>return</dt><dd><p>Download progress (in percentage) for the issue or volume</p></dd></dl>
/// \param issueId Global id of an issue
///
/// \param volumeId Global id of a volume
- (NSInteger)findDownloadProgress:(NSString * __nullable)volumeId issueId:(NSString * __nullable)issueId;

/// Get issue/volume ids whose download not complete yet
///
/// <dl><dt>return</dt><dd><p>array with issue/volume ids whose download is not complete</p></dd></dl>
- (NSArray * __nullable)getActiveDownloads;
@end



/// A model object for Purchases 
SWIFT_CLASS("_TtC9Dumpling28Purchase")
@interface Purchase : RLMObject

/// Apple id/SKU of the purchase made - article or issue
@property (nonatomic, copy) NSString * __nonnull appleId;

/// Global id of the purchase made - article, issue or volume
@property (nonatomic, copy) NSString * __nonnull globalId;

/// Mode of purchase - Web (could be any - Stripe or any other), IAP
@property (nonatomic, copy) NSString * __nonnull mode;

/// Type of purchase - article, issue or volume
@property (nonatomic, copy) NSString * __nonnull type;

/// Purchase date
@property (nonatomic) NSDate * __nonnull purchaseDate;

/// Expiration date
@property (nonatomic, copy) NSString * __nonnull expirationDate;

/// Identity used for syncing web purchases
@property (nonatomic, copy) NSString * __nonnull userIdentity;
- (SWIFT_NULLABILITY(null_unspecified) instancetype)init OBJC_DESIGNATED_INITIALIZER;
- (SWIFT_NULLABILITY(null_unspecified) instancetype)initWithObject:(id __null_unspecified)object OBJC_DESIGNATED_INITIALIZER;
@end


@interface RLMArray (SWIFT_EXTENSION(Dumpling2))
@end


@interface RLMObject (SWIFT_EXTENSION(Dumpling2))
@end


@interface RLMResults (SWIFT_EXTENSION(Dumpling2))
@end



/// Class which helps store and retrieve user reading status 
SWIFT_CLASS("_TtC9Dumpling212ReaderHelper")
@interface ReaderHelper : NSObject

/// Save current active volume
///
/// \param volumeId Global id of the volume which is currently being viewed. If nil, will remove saved volume
+ (void)saveVolume:(NSString * __nullable)volumeId;

/// Save current active issue
///
/// \param issueId Global id of the issue which is currently being viewed. If nil, will remove saved issue
+ (void)saveIssue:(NSString * __nullable)issueId;

/// Save current active article
///
/// \param articleId Global id of the article which is currently being viewed. If nil, will remove saved article
+ (void)saveArticle:(NSString * __nullable)articleId;

/// Save asset being viewed
///
/// \param assetId Global id of the asset which is currently being viewed. If nil, will remove saved asset
+ (void)saveAsset:(NSString * __nullable)assetId;

/// Save reading status for current article
///
/// \param articleId Global id of the article currently being read
///
/// \param readingPercentage Current position of user in the article in percentage
+ (void)saveReadingPercentageFor:(NSString * __nonnull)articleId readingPercentage:(float)readingPercentage;

/// Get current active volume
///
/// <dl><dt>return</dt><dd><p>global id of active volume or nil</p></dd></dl>
+ (NSString * __nullable)retrieveCurrentVolume;

/// Get current active issue
///
/// <dl><dt>return</dt><dd><p>global id of active issue or nil</p></dd></dl>
+ (NSString * __nullable)retrieveCurrentIssue;

/// Get current active article
///
/// <dl><dt>return</dt><dd><p>global id of active article or nil</p></dd></dl>
+ (NSString * __nullable)retrieveCurrentArticle;

/// Get current active asset
///
/// <dl><dt>return</dt><dd><p>global id of active asset or nil</p></dd></dl>
+ (NSString * __nullable)retrieveCurrentAsset;

/// Get last saved reading percentage for given article
///
/// <dl><dt>return</dt><dd><p>progress of given article's reading in percentage</p></dd></dl>
/// \param articleId Global id of article for which reading percentage is to be retrieved
+ (float)getReadingPercentageFor:(NSString * __nonnull)articleId;

/// Get all saved values for current issue, article, asset and reading percent for an article
///
/// <dl><dt>return</dt><dd><p>a dictionary containing saved values for current issue, article, asset and reading percentage for an article</p></dd></dl>
+ (NSDictionary * __nonnull)getDictionaryForCloud;

/// This method saves specific values from a key for current issue, current article, current asset and article reading percentage back to user defaults (for using while app is active)
///
/// <dl><dt>brief</dt><dd><p>Saves current reading status to User defaults</p></dd></dl>
/// \param savedValues a dictionary containing saved values for current issue, article, asset and reading percentage for an article
+ (void)saveDictionaryToUserDefaults:(NSDictionary * __nonnull)savedValues;
- (SWIFT_NULLABILITY(nonnull) instancetype)init OBJC_DESIGNATED_INITIALIZER;
@end



/// A model object for Volumes 
SWIFT_CLASS("_TtC9Dumpling26Volume")
@interface Volume : RLMObject

/// Global id of a volume - this is unique for each volume
@property (nonatomic, copy) NSString * __nonnull globalId;

/// Title of the volume
@property (nonatomic, copy) NSString * __nonnull title;

/// Subtitle of the volume
@property (nonatomic, copy) NSString * __nonnull subtitle;

/// Description of the volume
@property (nonatomic, copy) NSString * __nonnull volumeDesc;

/// Folder saving all the assets for the issue
@property (nonatomic, copy) NSString * __nonnull assetFolder;

/// Global id of the asset which is the cover image of the issue
@property (nonatomic, copy) NSString * __nonnull coverImageId;

/// Publisher of the volume
@property (nonatomic, copy) NSString * __nonnull publisher;

/// Published date for the volume
@property (nonatomic) NSDate * __nonnull publishedDate;

/// Release date for the volume
@property (nonatomic, copy) NSString * __nonnull releaseDate;

/// Custom metadata of the volume
@property (nonatomic, copy) NSString * __nonnull metadata;

/// Keywords for the volume
@property (nonatomic, copy) NSString * __nonnull keywords;

/// Whether the volume is published or not
@property (nonatomic) BOOL published;
+ (NSString * __nonnull)primaryKey;

/// This method uses the global id for a volume and deletes it from the database. All the volume's issues, assets, articles, issue assets, article assets are deleted from the database and the file system
///
/// <dl><dt>brief</dt><dd><p>Delete a volume</p></dd></dl>
/// \param globalId The global id for the volume
+ (void)deleteVolume:(NSString * __nonnull)globalId;

/// This method returns the Volume object for the most recent volume in the database (sorted by publish date)
///
/// <dl><dt>brief</dt><dd><p>Find most recent volume</p></dd></dl>
/// <dl><dt>return</dt><dd><p>Object for most recent volume</p></dd></dl>
+ (Volume * __nullable)getNewestVolume;

/// This method returns all volumes with specific keywords
///
/// <dl><dt>return</dt><dd><p>an array of volumes fulfiling the conditions</p></dd></dl>
/// \param keywords An array of String values with keywords that the volume should have. If any of the keywords match, the volume will be selected
+ (NSArray * __nullable)searchVolumesWith:(NSArray * __nonnull)keywords;

/// This method returns all volumes
///
/// <dl><dt>return</dt><dd><p>an array of volumes</p></dd></dl>
+ (NSArray * __nullable)getVolumes;

/// This method saves a volume back to the database
///
/// <dl><dt>brief</dt><dd><p>Save a volume to the database</p></dd></dl>
- (void)saveVolume;

/// This method returns the value for a specific key from the custom metadata of the volume
///
/// <dl><dt>brief</dt><dd><p>Get value for a specific key from custom meta of a volume</p></dd></dl>
/// <dl><dt>return</dt><dd><p>an object for the key from the custom metadata (or nil)</p></dd></dl>
- (id __nullable)getValue:(NSString * __nonnull)key;

/// This method returns all volumes whose publish date is older than the published date of current volume
///
/// <dl><dt>brief</dt><dd><p>Get all volumes older than a specific volume</p></dd></dl>
/// <dl><dt>return</dt><dd><p>an array of volumes older than the current volume</p></dd></dl>
- (NSArray * __nullable)getOlderVolumes;

/// This method returns all volumes whose publish date is newer than the published date of current volume
///
/// <dl><dt>brief</dt><dd><p>Get all volumes newer than a specific volume</p></dd></dl>
/// <dl><dt>return</dt><dd><p>an array of volumes newer than the current volume</p></dd></dl>
- (NSArray * __nullable)getNewerVolumes;
- (SWIFT_NULLABILITY(null_unspecified) instancetype)init OBJC_DESIGNATED_INITIALIZER;
- (SWIFT_NULLABILITY(null_unspecified) instancetype)initWithObject:(id __null_unspecified)object OBJC_DESIGNATED_INITIALIZER;
@end



/// Starter class which adds volumes to the database 
SWIFT_CLASS("_TtC9Dumpling213VolumeHandler")
@interface VolumeHandler : NSObject

/// Instance of IssueHandler class
@property (nonatomic) IssueHandler * __null_unspecified issueHandler;

/// Initializes the VolumeHandler with the given folder. This is where the database and assets will be saved. The method expects to find a key <code>ClientKey</code> in the project's Info.plist with your client key. If none is found, the method returns a nil
///
/// <dl><dt>brief</dt><dd><p>Initializer object</p></dd></dl>
/// \param folder The folder where the database and downloaded assets should be saved
- (SWIFT_NULLABILITY(nullable) instancetype)initWithFolder:(NSString * __nonnull)folder OBJC_DESIGNATED_INITIALIZER;

/// Initializes the VolumeHandler with the Documents directory. This is where the database and assets will be saved. The API key is used for making calls to the Magnet API
///
/// <dl><dt>brief</dt><dd><p>Initializer object</p></dd></dl>
/// \param clientkey Client API key to be used for making calls to the Magnet API
- (SWIFT_NULLABILITY(nonnull) instancetype)initWithClientkey:(NSString * __nonnull)clientkey OBJC_DESIGNATED_INITIALIZER;

/// Initializes the VolumeHandler with a custom directory. This is where the database and assets will be saved. The API key is used for making calls to the Magnet API
///
/// <dl><dt>brief</dt><dd><p>Initializer object</p></dd></dl>
/// \param folder The folder where the database and downloaded assets should be saved
///
/// \param clientkey Client API key to be used for making calls to the Magnet API
- (SWIFT_NULLABILITY(nonnull) instancetype)initWithFolder:(NSString * __nonnull)folder clientkey:(NSString * __nonnull)clientkey OBJC_DESIGNATED_INITIALIZER;

/// Find current schema version
///
/// <dl><dt>return</dt><dd><p>the current schema version for the database</p></dd></dl>
+ (NSUInteger)getCurrentSchemaVersion;

/// The method uses the global id of a volume, gets its content from the Magnet API and adds it to the database
///
/// <dl><dt>brief</dt><dd><p>Get Volume details from API and add to database</p></dd></dl>
/// \param globalId The global id for the volume
- (void)addVolumeFromAPI:(NSString * __nonnull)globalId;

/// This method gets all available volumes for a client key, downloads it and saves it to the database
- (void)addAllVolumes;

/// Get volume details from database for a specific global id
///
/// <dl><dt>return</dt><dd><p>Volume object or nil if the volume is not in the database</p></dd></dl>
/// \param volumeId global id of the volume
- (Volume * __nullable)getVolume:(NSString * __nonnull)volumeId;
- (void)listVolumes;
@end

#pragma clang diagnostic pop
