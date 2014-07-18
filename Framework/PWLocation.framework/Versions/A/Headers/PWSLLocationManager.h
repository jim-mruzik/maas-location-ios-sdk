//
//  PWSLLocationManager.h
//  PWLocation
//
//  Created by Illya Busigin on 7/9/14.
//  Copyright (c) 2014 Phunware Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

#import <PWLocation/PWLocationManager.h>
#import <PWLocation/PWIndoorLocation.h>

@protocol PWSLLocationManagerDelegate;

/**
 The `PWSLLocationManager` class defines the interface for configuring the delivery of BLE location-related events to your application. You use an instance of this class to establish the parameters that determine when location events should be delivered and to start and stop the actual delivery of those events. This class conforms to the `PWLocationManager` protocol.
 */

@interface PWSLLocationManager : NSObject <PWLocationManager>

/**
 The latest indoor location got from BLE location service.
 */
@property (nonatomic, readonly) PWIndoorLocation *location;

/**
 The floorIDMapping is the mapping of BLE floorID and Phunware floorID.
 */

@property (nonatomic, strong) NSDictionary *floorIDMapping;

/**
The mapID obtain from Phunware for the BLE location manager. (read-only)
 */

@property (nonatomic, readonly) NSString *mapID;

/**
 The customerID obtain from Phunware for the BLE location manager. (read-only)
 */

@property (nonatomic, readonly) NSString *customerID;

/**
 Initializes the location manager with the specified venue GUID and the venue location.
 @param mapID - Obtained from Phunware.
 @param customerID - Obtained from Phunware.
 @param venueLocation - The location of the venue.
 @discussion If the device is not within 5 kilometers of the venue location, then location updates will fail.
 @return The location manager object.
 */

- (instancetype)initWithMapIdentifier:(NSString *)mapID customerIdentifier:(NSString *)customerID location:(CLLocationCoordinate2D)venueLocation;

- (BOOL)locationServicesAvailable;
- (void)startUpdatingLocation;
- (void)stopUpdatingLocation;

@end


/**
 The `PWSLLocationManagerDelegate` protocol defines the methods used to receive location updates from a `PWLocationManager` object.
 
 The methods of your delegate object are called from the main application thread.
 */

@protocol PWSLLocationManagerDelegate <PWLocationManagerDelegate>

/**
 Tells the delegate that a new location update is available.
 @param manager The location manager object that generated the update event.
 @param location A location object with the updated location information. This object conforms to the `PWLocation` protocol.
 @discussion Implementation of this method is optional but recommended.
 */
- (void)locationManager:(id<PWLocationManager>)manager didUpdateToLocation:(id<PWLocation>)location;

/**
 Tells the delegate that the location manager was unable to retrieve a location value.
 @param manager The location manager object that was unable to retrieve the location.
 @param error The error object containing the reason the location could not be retrieved.
 @discussion Implementation of this method is optional but recommended.
 
 The location manager calls this method when it encounters an error trying to get the location data. If an error is encountered, the location manager will keep attempting to update until `stopUpdatingLocation` is called.
 */
- (void)locationManager:(id<PWLocationManager>)manager failedWithError:(NSError *)error;

@end