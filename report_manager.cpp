#include "report_manager.h"
#include <iostream>

void ReportManager::reportActiveReservations(ReservationManager& reservationManager) const {
    std::cout << "\n===== REPORT: Active Reservations =====\n";
    reservationManager.displayActiveReservations();
}

void ReportManager::reportResourceUtilization(ResourceManager& resourceManager,
                                                ReservationManager& reservationManager) const {
    std::cout << "\n===== REPORT: Resource Utilization =====\n";

    int total = resourceManager.getCount();
    if (total == 0) {
        std::cout << "No resources loaded.\n";
        return;
    }

    for (int i = 0; i < total; i++) {
        Resource r = resourceManager.getResourceAt(i);
        int reservationCount = reservationManager.countReservationsForResource(r.id);
        std::cout << r.name << " (ID " << r.id << "): "
                   << reservationCount << " reservation(s)\n";
    }
}

void ReportManager::reportMostRequestedResources(ResourceManager& resourceManager,
                                                   ReservationManager& reservationManager) const {
    std::cout << "\n===== REPORT: Most Requested Resources =====\n";

    int total = resourceManager.getCount();
    if (total == 0) {
        std::cout << "No resources loaded.\n";
        return;
    }

    
    Resource* resArr = new Resource[total];
    int* counts = new int[total];

    for (int i = 0; i < total; i++) {
        resArr[i] = resourceManager.getResourceAt(i);
        counts[i] = reservationManager.countReservationsForResource(resArr[i].id);
    }

    
    for (int i = 0; i < total - 1; i++) {
        int maxIdx = i;
        for (int j = i + 1; j < total; j++) {
            if (counts[j] > counts[maxIdx]) {
                maxIdx = j;
            }
        }
        if (maxIdx != i) {
            int tempCount = counts[i];
            counts[i] = counts[maxIdx];
            counts[maxIdx] = tempCount;

            Resource tempRes = resArr[i];
            resArr[i] = resArr[maxIdx];
            resArr[maxIdx] = tempRes;
        }
    }

    for (int i = 0; i < total; i++) {
        std::cout << (i + 1) << ". " << resArr[i].name
                   << " - " << counts[i] << " reservation(s)\n";
    }

    delete[] resArr;
    delete[] counts;
}

void ReportManager::reportWaitlistStatistics(ResourceManager& resourceManager, Waitlist& waitlist) const {
    std::cout << "\n===== REPORT: Waiting-List Statistics =====\n";

    int total = resourceManager.getCount();
    if (total == 0) {
        std::cout << "No resources loaded.\n";
        return;
    }

    for (int i = 0; i < total; i++) {
        Resource r = resourceManager.getResourceAt(i);
        int waitingCount = waitlist.countForResource(r.id);
        std::cout << r.name << " (ID " << r.id << "): "
                   << waitingCount << " student(s) waiting\n";
    }
}