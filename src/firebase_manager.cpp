#include "firebase_manager.h"
#define ENABLE_USER_AUTH
#include <Arduino.h>
#include <FirebaseClient.h>
#include <WiFiClientSecure.h>

#include "config.h"
#include "globals.h"


using namespace firebase_ns;


// =====================================================
// Firebase Objects
// =====================================================


WiFiClientSecure sslClient;


// Async Firebase Client
AsyncClientClass aClient(
    sslClient
);


FirebaseApp app;

UserAccount user(
    FIREBASE_API_KEY
);

RealtimeDatabase Database;



// =====================================================
// Firebase Status
// =====================================================

bool firebaseReady = false;



// =====================================================
// Initialize Firebase
// =====================================================

void initFirebase()
{

    Serial.println();
    Serial.println("==============================");
    Serial.println("Initializing Firebase...");
    Serial.println("==============================");


    sslClient.setInsecure();


    signup(
    aClient,
    app,
    getAuth(user)
);


    Database.url(
        FIREBASE_DATABASE_URL
    );


    firebaseConnected = false;


    Serial.println("Firebase Initialized");

};



// =====================================================
// Firebase Background Loop
// =====================================================

void firebaseLoop()
{

    // Required by FirebaseClient

    app.loop();



    if(app.ready())
    {

        firebaseReady = true;

        firebaseConnected = true;

    }
    else
    {

        firebaseReady = false;

        firebaseConnected = false;

    }

}



// =====================================================
// Firebase Synchronization
// =====================================================

void firebaseSync()
{

    if(!wifiConnected)
    {
        return;
    }



    if(!firebaseReady)
    {
        return;
    }



    Serial.println("Firebase Connected");

}



// =====================================================
// Firebase Status
// =====================================================

bool isFirebaseConnected()
{
    return firebaseConnected;
}