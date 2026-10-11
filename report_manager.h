#ifndef REPORT_MANAGER_H
#define REPORT_MANAGER_H

#include "resource_manager.h"
#include "reservation_manager.h"
#include "waitlist.h"


class ReportManager {
public:
    
    void reportActiveReservations(ReservationManager& reservationManager) const;

    
    void reportResourceUtilization(ResourceManager& resourceManager,
                                    ReservationManager& reservationManager) const;

    
    void reportMostRequestedResources(ResourceManager& resourceManager,
                                       ReservationManager& reservationManager) const;

    
    void reportWaitlistStatistics(ResourceManager& resourceManager, Waitlist& waitlist) const;
};

#endif