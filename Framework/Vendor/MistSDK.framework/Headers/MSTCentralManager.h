//
//  MSCentralManager.h
//  MistLocation
//
//  Created by Cisco on 1/23/15.
//  Copyright (c) 2015 Cisco . All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreBluetooth/CoreBluetooth.h>
#import <CoreLocation/CoreLocation.h>
#import <MapKit/MapKit.h>
#import "MSTEnum.h"
#import "MSTPoint.h"
#import "MSTMap.h"
#import "MSTUser.h"
#import "MSTAsset.h"
#import "MSTClient.h"
#import "MSTZone.h"
#import "MSTBeacon.h"
#import "MSTEnum.h"

@protocol MSTCentralManagerDelegate;
@protocol MSTProximityDelegate;

/**
 *  The Mist Manager is the manager of all the other managers. It offers the ability to connect to the Mist Cloud, start the desired services, stop and terminate connection.
 *  Methods:
 *  Start mist manager service
 *
 *  Stop mist manager service
 *
 *  Prepare GroundOverlayOptions
 *
 *  Set Map Origin
 *
 *  Get current Mist Location
 *  Get current OS location
 *  Get Map Origin
 *
 *  Subscribe to the MSTCentralManagerDelegate to be notified of Mist Location updates, and to get debug messages
 *
 */
@interface MSTCentralManager : NSObject

@property (nonatomic, weak) id<MSTCentralManagerDelegate> delegate;
@property (nonatomic, weak) id<MSTProximityDelegate> proximityDelegate;
//Options
@property (nonatomic) BOOL isSmoothingEnabled; //Private?

@property (nonatomic) bool isRunning;
@property (nonatomic) bool shouldShowVerboseLogs;

@property (nonatomic) NSUInteger smoothingNumber;

@property (nonatomic) bool shouldSendLocationResponseAlways;
@property (nonatomic) BOOL shouldSwitchToOSLocation;

@property (nonatomic) BOOL shouldDoJustMicroLocation;

// Analyze in/out time for Bob
@property (nonatomic, strong) NSMutableDictionary *requestHandlerCounterDict;
@property (nonatomic, strong) NSMutableArray *requestInTimeIntsDiffArr;
@property (nonatomic, strong) NSMutableDictionary *requestInTimeIntsHistoric;
@property (nonatomic) NSDate *previousOutDate;
@property (nonatomic) unsigned int minCounter;
@property (nonatomic) NSDate *previousInDate;
@property (nonatomic, strong) NSMutableDictionary *histogramInTime;
@property (nonatomic, strong) NSMutableDictionary *clientInformation;
@property (nonatomic) bool shouldCompressData;

/**
 *  Only send device motion if the user opt in, otherwise send NO for isDeviceMoving
 */
@property (nonatomic, assign) bool shouldSendDeviceIsMoving;

@property (nonatomic, strong) NSString *zoneName;
@property (nonatomic, strong) NSString *zoneType;
@property (nonatomic, strong) NSDate *zoneDate;

/**
 *  Set this property to true to send data via UDP, false will use TCP.
 */
@property (nonatomic) bool shouldUseUDP;
@property (nonatomic) bool shouldUseDeadReckoning;

//Initialization

/**
 *  Initialize the MSTCentralManager with orgID and orgSecret
 *
 *  @param orgId     tokenID for the organization
 *  @param orgSecret the tokenSecret for the organization
 *
 *  @return id an instance of MSTCentralManager
 */
- (id) initWithOrgID: (NSString *) orgId AndOrgSecret: (NSString *) orgSecret;

//App Information
#pragma marker -
#pragma marker - App information (optional)

- (void) setAppInfoWithName: (NSString *) appName andVersion: (NSString *) appVersion;

/**
 *  Start the location updates
 */
- (void) startLocationUpdates;

/**
 *  Stop the location updates
 */
- (void) stopLocationUpdates;

//Location Response

/**
 *  Get the current location in lat, long
 *
 *  @return Returns the current location in CLLocationCoordinate2D (lat,long).
 */
- (CLLocationCoordinate2D) getCurrentLocation;

/**
 *  Get the current location in X, Y relative to top left corner of the floorplan
 *
 *  @return Returns the current location in MSTPoint.
 */
- (MSTPoint *) getCurrentRelativeLocation;

//Mapping

/**
 *  Get the map origin
 *
 *  @return Returns the map origin in CLLocationCoordinate2D.
 */
- (CLLocationCoordinate2D) getMapOrigin;

/**
 *  Get the map ID
 *
 *  @return Returns the map identifier.
 */
- (NSString *) getMapId;

/**
 *  Get the map object.
 *
 *  @return Returns the map object in MSTMap.
 */
- (MSTMap *) getMapDetails;

/**
 *  Get the map name.
 *
 *  @return Returns the map name.
 */
- (NSString *) getMapName;

//Settings

/**
 *  Check if BLE power status is on.
 *
 *  @return Returns true or false for BLE power.
 */
- (BOOL) isBluetoothPowerOn;

/**
 *  Check if Location is authorized.
 *
 *  @return Returns true or false for Location authorization.
 */
- (BOOL) isLocationAuthorized;

/**
 *  Get the Location authorization status.
 *
 *  @return Returns the location authorization status.
 */
- (CLAuthorizationStatus) getLocationAuthorizationStatus;

- (void) requestAuthorization: (AuthorizationType) authorizationType;

-(void)saveClientInformation:(NSMutableDictionary *)clientInformation;

//#pragma mark - Error logging
//- (void) reportLogMessage: (NSString *) errorMessage;

#pragma mark - Background

-(void)setMonitoringInBackground:(NSArray *)regions;
-(void)setRangingInBackground:(NSArray *)regions;

/**
 * Setting that enables or disables wake up of the app using iBeacon regions
 *
 
 */

#pragma mark - Wake up app
- (void) wakeUpAppSetting: (BOOL) shouldWakeUpApp;

#pragma mark - Background app settings
- (void) backgroundAppSetting: (BOOL) shouldWorkInBackground;

#pragma mark -

//UNIMPLEMENTED
//Clients
- (NSArray *) getAllClients;
//Zones
- (NSArray *) getAllZones;
//Assets
- (NSArray *) getAllAssets;

- (void) resumeLocationUpdates;
- (void) pauseLocationUpdates;

-(void)alert:(NSDictionary *)msgDict;

#pragma mark -
//Test Only

#pragma mark - TEST only
@property (nonatomic) long timeElapsed;
@property (nonatomic) BOOL isAccuracyTestingOn;
@property (nonatomic) BOOL isStopAndGoDataCollection;
@property (nonatomic) BOOL isWalkTest;

- (NSString *) getDeviceId;
- (NSDictionary *) getDeviceInformation;
- (CLLocationCoordinate2D) getCurrentOSLocation;
- (NSString *) getResponseString;

//Test only APIs
- (void) setTopicName:(NSString *)topic;
- (void) setHostURL:(NSString *)hostUri;

/**
 *  Set the environment type to connect to the correct Mist environment.
 *
 *  @param envType - The values for this param is D,S,P.
 */
- (void) setEnviroment:(NSString *)envType;

- (CLLocationCoordinate2D) getLatitudeLongitudeUsingMapOriginForX: (double) x AndY: (double) y;

#pragma mark - App debugging
- (void) setShouldDoAppDebugging: (BOOL) shouldDoAppDebugging;
- (void) sendAppLogs: (NSDictionary *) appLog;
- (bool) isShouldDoAppDebugging;

#pragma mark - Data collection

- (void) setMarkerInformationWithDate:(NSString *)time MarkerX:(int)x AndY:(int)y;
- (void) setWalkMarkerInformationWithDate:(NSString *)time MarkerX:(int)x AndY:(int)y EndX: (int)endX AndEndY: (int)endY AndComments: (NSString *) walkComment;
- (void) startDataCollection;
- (void) stopDataCollection;
- (int) getCollectionCounter;
- (void) spottedVbeacon;
- (void) incrementStaticX;
- (void) incrementStaticY;
- (void) decrementStaticX;
- (void) decrementStaticY;
- (NSString *) currentStaticLocation;

/**
 *  Get accumulative transmitted data size;
 *
 *  @return size in bytes
 */
-(NSUInteger)getAccumulativeTXSize;

/**
 *  Get accumulative received data size;
 *
 *  @return size in bytes
 */
-(NSUInteger)getAccumulativeRXSize;

@end

@protocol MSTCentralManagerDelegate <NSObject>

#pragma mark - Old APIs
//TODO: Remove?

@optional
-(void)manager:(MSTCentralManager *) manager receive:(id)message;
-(void)manager:(MSTCentralManager *) manager receiveLogMessage: (NSString *)logMessages;

-(void)manager:(MSTCentralManager *) manager receivedLogMessage: (NSString *)message forCode:(MSTCentralManagerStatusCode)code;
-(void)manager:(MSTCentralManager *) manager receivedVerboseLogMessage: (NSString *)message;

-(void)manager:(MSTCentralManager *) manager notifications:(NSString *)notificationMessage;
-(void)manager:(MSTCentralManager *)manager restMessage: (NSString *)restMessage;//TODO: Debugging purposes. Need to remove

#pragma mark - New APIs

@optional

#pragma mark - Compass Callback
- (void) mistManager: (MSTCentralManager *) manager didUpdateHeading: (CLHeading *) headingInformation;

#pragma mark - Location Callbacks

// Relative location callback

/**
 *  Called when MistFramework receives a location update and retrieving map information.
 *
 *  @param manager          Returns the caller
 *  @param relativeLocation Returns the relative location
 *  @param maps             Returns the maps
 *  @param dateUpdated      Returns the timeUpdated
 */
-(void)mistManager: (MSTCentralManager *) manager willUpdateRelativeLocation: (MSTPoint *) relativeLocation inMaps: (NSArray *) maps at: (NSDate *) dateUpdated;

// didUpdateRelativeLocation
// INDOOR ONLY: This function is called when we have both relative location and the actual map details for rendering.

/**
 *  Called when MistFramework receives a location update and has map information.
 *
 *  @param manager          Returns the caller
 *  @param relativeLocation Returns the relative location
 *  @param maps             Returns the maps
 *  @param dateUpdated      Returns the timeUpdated
 */
-(void)mistManager: (MSTCentralManager *) manager didUpdateRelativeLocation: (MSTPoint *) relativeLocation inMaps: (NSArray *) maps at: (NSDate *) dateUpdated;

//-(void)mistManager: (MSTCentralManager *)manager didUpdateComputedLocation:(MSTPoint *)point inMaps:(NSArray *)maps at:(NSDate *)dateUpdated;
//
//-(void)mistManager: (MSTCentralManager *)manager didUpdateAverageLocation:(MSTPoint *)point inMaps:(NSArray *)maps at:(NSDate *)dateUpdated;

-(void)mistManager: (MSTCentralManager *)manager didUpdatePle:(NSInteger)ple andIntercept:(NSInteger)intercept inMaps:(NSArray *)maps at:(NSDate *)dateUpdated;

//Geolocation Callback

// willUpdateLocation
// INDOOR ONLY: This function is called when we have a location but the actual map details are not yet available. SourceType will always be MIST

-(void) mistManager: (MSTCentralManager *) manager willUpdateLocation: (CLLocationCoordinate2D) location inMaps: (NSArray *) maps withSource: (SourceType) locationSource  at: (NSDate *) dateUpdated;

// didUpdateRelativeLocation
// INDOOR and OUTDOOR: This function is called when we have both relative location and the actual map details.
/*
    SourceType:
    OS Location - This type will be returned when Bluetooth is turned off or beacons have not been detected. Most likely when the user is outdoor.
    MIST Location - This type will be returned when Bluetooth is turned on and beacons have been detected.
 */

-(void) mistManager: (MSTCentralManager *) manager didUpdateLocation: (CLLocationCoordinate2D) location inMaps: (NSArray *) maps withSource: (SourceType) locationSource  at: (NSDate *) dateUpdated;

//Accuracy of the location callback
//This function is called only when we have a location (relative or geolocation)

- (void) mistManager:(MSTCentralManager *)manager didLocateWithProbability: (double) probability andRadius: (double) radius at: (NSString *) dateUpdated;

#pragma mark - Beacon Callbacks

// Beacon callbacks

-(void) mistManager: (MSTCentralManager *) manager didRangeBeacons:(NSArray *)beacons inRegion: (CLRegion *) region  at: (NSDate *) dateUpdated;

// Beacon list callbacks

-(void) mistManager: (MSTCentralManager *) manager didUpdateBeaconList:(NSArray *)beaconUuids  at: (NSDate *) dateUpdated;

#pragma mark - virtual beacons

-(void)mistManager:(MSTCentralManager *)manager didReceivedVirtualBeacons:(NSDictionary *)virtualBeacons;

#pragma mark - client information

-(void)mistManager:(MSTCentralManager *)manager didReceivedClientInformation:(NSDictionary *)clientInformation;

#pragma mark - virtual beacon proximity

-(void)startVirtualBeaconProximity:(CGPoint)currentLocation;

#pragma mark - STUBS

//Zone Stats callback
-(void) mistManager: (MSTCentralManager *) manager didUpdateZoneStats: (NSArray *)zones  at: (NSDate *) dateUpdated;
//User callback
-(void) mistManager: (MSTCentralManager *) manager didUpdateClients: (NSArray *)clients inZones: (NSArray *) zones  at: (NSDate *) dateUpdated;
//Asset callback
-(void) mistManager: (MSTCentralManager *)manager didUpdateAssets: (NSArray *)assets inZones: (NSArray *) zones  at: (NSDate *) dateUpdated;

#pragma mark - Background Mode

-(void)manager:(MSTCentralManager *)manager didUpdateLocations:(NSArray *)locations;
-(void)manager:(MSTCentralManager *)manager didDetermineState:(CLRegionState)state forRegion:(CLRegion *)region;
-(void)manager:(MSTCentralManager *)manager didRangeBeacons:(NSArray *)beacons inRegion:(CLBeaconRegion *)region;

#pragma mark -

#pragma mark - Health Callbacks

// Health of connection callback

// didConnect
// This function is a little indicator letting the user knows it's connected

- (void) mistManager:(MSTCentralManager *)manager didConnect: (BOOL) isConnected;

//Error message callback
//This function is called to give an insight into any issues that might be occurring

- (void) manager:(MSTCentralManager *)manager didErrorOccurWithType: (ErrorType) errorType andDetails: (NSString *) errorDetails;

#pragma mark - Map Callbacks

// Map callback

/**
 *  Called when a map is being detected and fetched from the backend. This function will not be called when bluetooth is not turned on, hence it is for indoor purposes
 *
 *  @param manager     Returns the caller
 *  @param map         Returns the new map information
 *  @param dateUpdated Returns the date updated.
 */
- (void) mistManager: (MSTCentralManager *) manager didUpdateMap: (MSTMap *) map at: (NSDate *) dateUpdated;

- (void) mistManager:(MSTCentralManager *)manager didUpdateLocationDate: (NSString *) locationUpdateDate;

#pragma mark - Setting Callbacks

// Settings callback

/**
 *  Called when setting type has changed
 *
 *  @param manager   Returns the caller
 *  @param isEnabled Returns the updated status.
 *  @param type      Returns the type of setting in MSTCentralManagerSettingType.
 */
-(void)mistManager:(MSTCentralManager *)manager didUpdateStatus:(MSTCentralManagerSettingStatus)isEnabled ofSetting:(MSTCentralManagerSettingType)type;

-(void)mistManager:(MSTCentralManager *)manager beaconsSent:(NSMutableArray *)beacons;

-(void)mistManager:(MSTCentralManager *)manager time:(double)time sinceSentForCounter:(NSString *)index;

-(void)mistManager:(MSTCentralManager *)manager restartScan:(NSString *)message;

-(void)mistManager:(MSTCentralManager *)manager didReceiveNotificationMessage:(NSDictionary *)payload;

-(void)mistManager:(MSTCentralManager *)manager didUpdateProximityToMinor: (int) minor;

-(void)mistManager:(MSTCentralManager *)manager :(NSString *)message;

#pragma mark data in/out for Bob

-(void)mistManager:(MSTCentralManager *)manager requestOutTimeInt:(NSTimeInterval)interval;
-(void)mistManager:(MSTCentralManager *)manager requestInTimeInts:(NSArray *)timeInts;
-(void)mistManager:(MSTCentralManager *)manager requestInTimeIntsHistoric:(NSDictionary *)timeIntsHistoric;

#pragma mark 
- (void) mistManager:(MSTCentralManager *)manager alert: (NSString *) message;

#pragma mark Stats
- (void)mistManager:(MSTCentralManager *)manager didUpdateLatencyStats: (double) deviceLatency andBackendRtt: (double) backendRtt;
- (void)mistManager:(MSTCentralManager*)manager didUpdateNetworkLatency: (double) networkLatency;

@end