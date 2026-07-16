#ifndef FIREBASE_MANAGER_H
#define FIREBASE_MANAGER_H

#include <Arduino.h>


void initFirebase();

void firebaseLoop();

void firebaseSync();

bool isFirebaseConnected();


#endif