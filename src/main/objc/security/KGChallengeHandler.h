/**
 * Copyright (c) 2007-2014 Kaazing Corporation. All rights reserved.
 * 
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 * 
 *   http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied.  See the License for the
 * specific language governing permissions and limitations
 * under the License.
 */

#import <Foundation/Foundation.h>

#import "KGChallengeRequest.h"
#import "KGChallengeResponse.h"

@class KGChallengeResponse;
/**
 * A ChallengeHandler is responsible for producing responses to authentication challenges.
 * <p/>
 * When an attempt to access a protected URI is made, the server responsible for serving the resource
 * may respond with authentication challenge, indicating that credentials need be provided before access to the
 * resource is granted.  The specific type of challenge is indicated in a HTTP header called "WWW-Authenticate".
 * This response and that header are converted into a KGChallengeRequest and sent to a
 * registered ChallengeHandler for authentication challenge responses.  The KGChallengeResponse credentials
 * generated by a registered challenge handler are included in a replay of the original  request to the server, which
 * (assuming the credentials are sufficient) allows access to the resource.
 * <p/>
 * Public subclasses of ChallengeHandler can be loaded and instantiated using KGChallengeHandlers,
 * and registered to handle server challenges for specific URI locations
 * using KGDispatchChallengeHandler register method.
 * <p/>
 * Any challenge responses to requests matching the registered location may be handled by the registered KGChallengeHandler
 * as long as canHandle returns true.  In the case where multiple registered challenge handlers
 * could respond to a challenge request, the earliest challenge handler registered at the most specific location matching
 * the protected URI is selected.
 *
 */
@interface KGChallengeHandler : NSObject

/**
 * Can the presented challenge be potentially handled by this challenge handler?
 *
 * @param challengeRequest a challenge request object containing a challenge
 * @return true if this challenge handler could potentially respond meaningfully to the challenge.
 */
- (BOOL) canHandle:(KGChallengeRequest *) challengeRequest;

/**
 * Handle the presented challenge by creating a challenge response or returning nil.
 * This responsibility is usually achieved
 * by using the associated KGLoginHandler to obtain user credentials, and transforming those credentials
 * into a KGChallengeResponse.
 * <p/>
 * When it is not possible to create a KGChallengeResponse, this method MUST return nil.
 *
 * @param challengeRequest a challenge object
 * @return a challenge response object or nil if no response is possible.
 */
- (KGChallengeResponse *) handle:(KGChallengeRequest *) challengeRequest;

+ (id) create;

@end
