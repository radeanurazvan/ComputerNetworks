#include "stdio.h"

#include "AuthGuard.h"
#include "../Settings/Settings.h"

bool AuthGuard::IsAuthenticated() {
    auto file =  fopen(Settings::sessionPath, "r");
    if(file != NULL) {
        fclose(file);
        return true;
    } 

    return false;
}