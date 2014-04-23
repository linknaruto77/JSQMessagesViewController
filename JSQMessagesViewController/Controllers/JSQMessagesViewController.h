//
//  Created by Jesse Squires
//  http://www.hexedbits.com
//
//
//  Documentation
//  http://cocoadocs.org/docsets/JSMessagesViewController
//
//
//  The MIT License
//  Copyright (c) 2014 Jesse Squires
//  http://opensource.org/licenses/MIT
//

#import <UIKit/UIKit.h>

#import "JSQMessagesCollectionView.h"
#import "JSQMessagesCollectionViewFlowLayout.h"

@class JSQMessagesViewController;
@class JSQMessagesInputToolbar;
@class JSQMessage;

/**
 *  The `JSQMessagesViewController` class represents a view controller whose content consists of 
 *  a `JSQMessagesCollectionView` and `JSQMessagesInputToolbar` and is specialized to display a messaging interface.
 */
@interface JSQMessagesViewController : UIViewController <JSQMessagesCollectionViewDataSource,
                                                         JSQMessagesCollectionViewDelegateFlowLayout>

/**
 *  Returns the collection view object managed by this view controller. 
 *  This view controller is the collection view's data source and delegate.
 */
@property (weak, nonatomic, readonly) JSQMessagesCollectionView *collectionView;

/**
 *  Returns the input toolbar view object managed by this view controller. 
 *  This view controller is the toolbar's delegate.
 */
@property (weak, nonatomic, readonly) JSQMessagesInputToolbar *inputToolbar;

/**
 *  The name of the user sending messages. This value must not be `nil`. 
 *  The default value is `@"JSQDefaultSender"`.
 */
@property (copy, nonatomic) NSString *sender;

/**
 *  Specifies whether or not the view controller should automatically scroll to the most recent message 
 *  when the view appears and when sending, receiving, and composing a new message.
 *
 *  @discussion The default value is `YES`, which allows the view controller to scroll automatically to the most recent message. 
 *  Set to `NO` if you want to manage scrolling yourself.
 */
@property (assign, nonatomic) BOOL automaticallyScrollsToMostRecentMessage;

/**
 *  The collection view cell identifier to use for dequeuing outgoing message collection view cells in the collectionView.
 *
 *  @discussion The default value is the string returned by `[JSQMessagesCollectionViewCellOutgoing cellReuseIdentifier]`. 
 *  This value must not be `nil`.
 *  
 *  @see JSQMessagesCollectionViewCellOutgoing.
 *
 *  @warning Overriding this property's default value is *not* recommended. 
 *  You should only override this property's default value if you are proividing your own cell prototypes.
 *  These prototypes must be registered with the collectionView for reuse and you are then responsible for 
 *  completely overriding many delegate and data source methods for the collectionView, 
 *  including `collectionView: cellForItemAtIndexPath:`.
 */
@property (copy, nonatomic) NSString *outgoingCellIdentifier;

/**
 *  The collection view cell identifier to use for dequeuing incoming message collection view cells in the collectionView.
 *
 *  @discussion The default value is the string returned by `[JSQMessagesCollectionViewCellIncoming cellReuseIdentifier]`. 
 *  This value must not be `nil`.
 *
 *  @see JSQMessagesCollectionViewCellIncoming.
 *
 *  @warning Overriding this property's default value is *not* recommended. 
 *  You should only override this property's default value if you are proividing your own cell prototypes. 
 *  These prototypes must be registered with the collectionView for reuse and you are then responsible for 
 *  completely overriding many delegate and data source methods for the collectionView, 
 *  including `collectionView: cellForItemAtIndexPath:`.
 */
@property (copy, nonatomic) NSString *incomingCellIdentifier;

/**
 *  The color for the typing indicator for incoming messages.
 *
 *  @discussion The color specified is used for the typing indicator bubble image color.
 *  This color is then slightly darkened and used to color the typing indicator ellipsis.
 *  The default value is the light gray color value return by `jsq_messageBubbleLightGrayColor`.
 */
@property (strong, nonatomic) UIColor *typingIndicatorColor;

/**
 *  Specifies whether or not the view controller should show the typing indicator for an incoming message.
 *  @discussion Setting this property to `YES` will animate showing the typing indicator immediately.
 *  Setting this property to `NO` will animate hiding the typing indicator immediately.
 */
@property (assign, nonatomic) BOOL showTypingIndicator;

#pragma mark - Class methods

/**
 *  Returns the `UINib` object initialized for `JSQMessagesViewController`.
 *
 *  @return The initialized `UINib` object or `nil` if there were errors during initialization 
 *  or the nib file could not be located.
 */
+ (UINib *)nib;

/**
 *  Creates and returns a new `JSQMessagesViewController` object.
 *
 *  @return The initialized messages view controller if successful, otherwise `nil`.
 */
+ (instancetype)messagesViewController;

#pragma mark - Messages view controller

/**
 *  This method is called when the user taps the send button on the `inputToolbar` after composing the specified message.
 *
 *  @param sender  The send button that was pressed by the user.
 *  @param message The message composed by the user.
 */
- (void)didPressSendButton:(UIButton *)sender withMessage:(JSQMessage *)message;

/**
 *  This method is called when the user taps the accessory button on the `inputToolbar`.
 *
 *  @param sender The accessory button that was pressed by the user.
 */
- (void)didPressAccessoryButton:(UIButton *)sender;

/**
 *  Completes the "sending" of a new message by animating and resetting the `inputToolbar`, 
 *  animating the addition of a new collection view cell in the collection view,
 *  reloading the collection view, and scrolling to the newly sent message 
 *  as specified by `automaticallyScrollsToMostRecentMessage`.
 *
 *  @discussion You should call this method at the end of `didPressSendButton: withMessage:` 
 *  after adding the new message to your data source and performing any related tasks.
 *
 *  @see `automaticallyScrollsToMostRecentMessage`.
 *  @see `didPressSendButton: withMessage:`.
 */
- (void)finishSending;

/**
 *  Scrolls the collection view such that the bottom most cell is completely visible, above the `inputToolbar`.
 *
 *  @param animated Pass `YES` if you want to animate scrolling, `NO` if it should be immediate.
 */
- (void)scrollToBottomAnimated:(BOOL)animated;

@end