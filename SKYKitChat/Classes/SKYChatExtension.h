//
//  SKYContainer+Chat.h
//  SKYKit
//
//  Copyright 2016 Oursky Ltd.
//
//  Licensed under the Apache License, Version 2.0 (the "License");
//  you may not use this file except in compliance with the License.
//  You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
//  Unless required by applicable law or agreed to in writing, software
//  distributed under the License is distributed on an "AS IS" BASIS,
//  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//  See the License for the specific language governing permissions and
//  limitations under the License.

#import <SKYKit/SKYKit.h>

typedef NS_ENUM(int, SKYChatMetaDataType) {
    SKYChatMetaDataImage,
    SKYChatMetaDataVoice,
    SKYChatMetaDataText
};

extern NSString *_Nonnull const SKYChatMetaDataAssetNameImage;
extern NSString *_Nonnull const SKYChatMetaDataAssetNameVoice;
extern NSString *_Nonnull const SKYChatMetaDataAssetNameText;

@class SKYConversation, SKYMessage, SKYUserChannel, SKYLastMessageRead, SKYUserConversation;

@interface SKYChatExtension : NSObject

typedef void (^SKYChatUserConversationCompletion)(SKYUserConversation *_Nullable conversation,
                                                  NSError *_Nullable error);
typedef void (^SKYChatMessageCompletion)(SKYMessage *_Nullable message, NSError *_Nullable error);
typedef void (^SKYChatMarkLastMessageReadCompletion)(SKYUserConversation *_Nullable conversation,
                                                     NSError *_Nullable error);
typedef void (^SKYChatLastMessageReadCompletion)(SKYLastMessageRead *_Nullable lastMessageRead,
                                                 NSError *_Nullable error);
typedef void (^SKYChatTotalUnreadCountCompletion)(NSDictionary *_Nullable response,
                                                  NSError *_Nullable error);
typedef void (^SKYChatUnreadCountCompletion)(NSInteger count, NSError *_Nullable error);
typedef void (^SKYChatChannelCompletion)(SKYUserChannel *_Nullable userChannel,
                                         NSError *_Nullable error);
typedef void (^SKYChatGetUserConversationListCompletion)(
    NSArray<SKYUserConversation *> *_Nullable conversationList, NSError *_Nullable error);
typedef void (^SKYChatGetMessagesListCompletion)(NSArray<SKYMessage *> *_Nullable messageList,
                                                 NSError *_Nullable error);
typedef void (^SKYChatGetAssetsListCompletion)(SKYAsset *_Nullable assets,
                                               NSError *_Nullable error);
typedef void (^SKYChatConversationCompletion)(SKYConversation *_Nullable conversation,
                                              NSError *_Nullable error);

@property (strong, nonatomic, readonly, nonnull) SKYContainer *container;

- (nullable instancetype)initWithContainer:(nonnull SKYContainer *)container;

#pragma mark - Conversations

- (void)createConversationWithParticipantIDs:(NSArray<NSString *> *_Nonnull)participantIds
                                    adminIDs:(NSArray<NSString *> *_Nonnull)adminIds
                                       title:(NSString *_Nullable)title
                           completionHandler:
                               (SKYChatConversationCompletion _Nullable)completionHandler;

- (void)fetchOrCreateDirectConversationWithUserId:(NSString *_Nonnull)userId
                                completionHandler:
                                    (SKYChatConversationCompletion _Nullable)completionHandler;

- (void)deleteConversation:(SKYConversation *_Nonnull)conversation
         completionHandler:(SKYChatConversationCompletion _Nullable)completionHandler;

- (void)deleteConversationWithID:(NSString *_Nonnull)conversationId
               completionHandler:(SKYChatConversationCompletion _Nullable)completionHandler;

- (void)saveConversation:(SKYConversation *_Nonnull)conversation
       completionHandler:(SKYChatConversationCompletion _Nullable)completionHandler;

#pragma mark Fetching User Conversations

- (void)fetchUserConversationsCompletionHandler:
    (SKYChatGetUserConversationListCompletion _Nullable)completionHandler;

- (void)fetchUserConversationWithID:(NSString *_Nonnull)conversationId
                  completionHandler:(SKYChatUserConversationCompletion _Nullable)completionHandler;

#pragma mark Conversation Memberships

- (void)addParticipantsWithIDs:(NSArray<NSString *> *_Nonnull)participantIDs
                toConversation:(SKYConversation *_Nonnull)conversation
             completionHandler:(SKYChatConversationCompletion _Nullable)completionHandler;

- (void)removeParticipantsWithIDs:(NSArray<NSString *> *_Nonnull)participantIDs
                 fromConversation:(SKYConversation *_Nonnull)conversation
                completionHandler:(SKYChatConversationCompletion _Nullable)completionHandler;

- (void)addAdminsWithIDs:(NSArray<NSString *> *_Nonnull)adminIDs
          toConversation:(SKYConversation *_Nonnull)conversation
       completionHandler:(SKYChatConversationCompletion _Nullable)completionHandler;

- (void)removeAdminsWithIDs:(NSArray<NSString *> *_Nonnull)adminIDs
           fromConversation:(SKYConversation *_Nonnull)conversation
          completionHandler:(SKYChatConversationCompletion _Nullable)completionHandler;

#pragma mark - Messages

- (void)createMessageWithConversation:(SKYConversation *_Nonnull)conversation
                                 body:(NSString *_Nullable)body
                             metadata:(NSDictionary *_Nullable)metadata
                    completionHandler:(SKYChatMessageCompletion _Nullable)completionHandler;

- (void)createMessageWithConversation:(SKYConversation *_Nonnull)conversation
                                 body:(NSString *_Nullable)body
                                image:(UIImage *_Nullable)image
                    completionHandler:(SKYChatMessageCompletion _Nullable)completionHandler;

- (void)createMessageWithConversation:(SKYConversation *_Nonnull)conversation
                                 body:(NSString *_Nullable)body
                         voiceFileURL:(NSURL *_Nullable)url
                             duration:(float)duration
                    completionHandler:(SKYChatMessageCompletion _Nullable)completionHandler;

- (void)addMessage:(SKYMessage *_Nonnull)message
       toConversation:(SKYConversation *_Nonnull)conversation
    completionHandler:(SKYChatMessageCompletion _Nullable)completionHandler;

- (void)addMessage:(SKYMessage *_Nonnull)message
             andAsset:(SKYAsset *_Nullable)asset
       toConversation:(SKYConversation *_Nonnull)conversation
    completionHandler:(SKYChatMessageCompletion _Nullable)completionHandler;

- (void)deleteMessage:(SKYMessage *_Nonnull)message
    completionHandler:(SKYChatMessageCompletion _Nullable)completionHandler;

- (void)deleteMessageWithID:(NSString *_Nonnull)messageID
          completionHandler:(SKYChatMessageCompletion _Nullable)completionHandler;

- (void)fetchMessagesWithConversation:(SKYConversation *_Nonnull)conversation
                                limit:(NSInteger)limit
                           beforeTime:(NSDate *_Nullable)beforeTime
                    completionHandler:(SKYChatGetMessagesListCompletion _Nullable)completionHandler;

- (void)fetchMessagesWithConversationID:(NSString *_Nonnull)conversationId
                                  limit:(NSInteger)limit
                             beforeTime:(NSDate *_Nullable)beforeTime
                      completionHandler:
                          (SKYChatGetMessagesListCompletion _Nullable)completionHandler;

#pragma mark Delivery and Read Status

- (void)markReadMessages:(NSArray<SKYMessage *> *_Nonnull)messages
       completionHandler:(void (^_Nullable)(NSError *_Nullable error))completionHandler;

- (void)markReadMessagesWithID:(NSArray<NSString *> *_Nonnull)messageIDs
             completionHandler:(void (^_Nullable)(NSError *_Nullable error))completionHandler;

- (void)markDeliveredMessages:(NSArray<SKYMessage *> *_Nonnull)messages
            completionHandler:(void (^_Nullable)(NSError *_Nullable error))completionHandler;

- (void)markDeliveredMessagesWithID:(NSArray<NSString *> *_Nonnull)messageIDs
                  completionHandler:(void (^_Nullable)(NSError *_Nullable error))completionHandler;

#pragma mark Message Markers

- (void)getOrCreateLastMessageReadithConversationId:(NSString *_Nonnull)conversationId
                                  completionHandler:
                                      (SKYChatLastMessageReadCompletion _Nullable)completionHandler;

- (void)markAsLastMessageReadWithConversationId:(NSString *_Nonnull)conversationId
                                  withMessageId:(NSString *_Nonnull)messageId
                              completionHandler:
                                  (SKYChatMarkLastMessageReadCompletion _Nullable)completionHandler;

- (void)getTotalUnreadCount:(SKYChatTotalUnreadCountCompletion _Nullable)completionHandler;

- (void)getUnreadMessageCountWithConversationId:(NSString *_Nonnull)conversationId
                              completionHandler:
                                  (SKYChatUnreadCountCompletion _Nullable)completionHandler;

- (void)getOrCreateUserChannelCompletionHandler:
    (SKYChatChannelCompletion _Nullable)completionHandler;

#pragma mark - Subscriptions

- (void)subscribeHandler:(void (^_Nonnull)(NSDictionary<NSString *, id> *_Nonnull))messageHandler;

#pragma mark - Assets

- (void)fetchAssetsByRecordId:(NSString *_Nonnull)recordId
            CompletionHandler:(SKYChatGetAssetsListCompletion _Nullable)completionHandler;

@end
