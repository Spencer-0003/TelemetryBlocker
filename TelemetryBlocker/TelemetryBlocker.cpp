#include <iostream>
#include <fstream>
#include "Endpoints.h"
using namespace std;

// Constants
const string HOSTS = "C:\\Windows\\System32\\drivers\\etc\\hosts";

// Methods
void appendFile(string file, string toAppend)
{
    ofstream outfile;
    outfile.open(file, ios_base::app);
    outfile << toAppend;
    outfile.close();
}

void blockMicrosoftTelemetry()
{
    appendFile(HOSTS, "\n# TelemetryBlocker (Block Microsoft Telemetry)\n");
    for (int i = 0; i < MicrosoftTelemetryEndpoints.size(); i++)
        appendFile(HOSTS, "0.0.0.0 " + MicrosoftTelemetryEndpoints[i] + "\n");
    cout << "\nBlocked Windows Telemetry\n\n";
}

void blockGoogleTelemetry() {
    appendFile(HOSTS, "\n# TelemetryBlocker (Ads & Tracking)\n");
    for (int i = 0; i < GoogleTrackingEndpoints.size(); i++)
        appendFile(HOSTS, "0.0.0.0 " + GoogleTrackingEndpoints[i] + "\n");
    cout << "\nBlocked Ads & Tracking Telemetry\n\n";
}

void blockMiscTrackersAndAds() {
    appendFile(HOSTS, "\n# TelemetryBlocker (Misc Ads & Tracking)\n");
    for (int i = 0; i < MiscAdsAndTrackingEndpoints.size(); i++)
        appendFile(HOSTS, "0.0.0.0 " + MiscAdsAndTrackingEndpoints[i] + "\n");
    cout << "\nBlocked Misc ads & Trackers\n";
}

// Main loop
int main()
{
    while (true) {
        int option;
        cout << "TelemetryBlocker (MAKE SURE YOU'RE RUNNING AS ADMINISTRATOR)\n\n1. Block Telemetry (Windows)\n2. Block Google Telemetry (Ads & Tracking)\n3. Block Misc Ads & Trackers \n\nChoose an option: ";
        cin >> option;

        if (!cin)
            break;

        switch (option) {
        case 1:
            blockMicrosoftTelemetry();
            break;
        case 2:
            blockGoogleTelemetry();
            break;
        case 3:
            blockMiscTrackersAndAds();
            break;
        default:
            cout << "Invalid option.\n\n";
            break;
        }
    }

    return 0;
}
