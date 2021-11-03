#include <iostream>
#include <filesystem>
#include <fstream>
#include "Endpoints.h"
using namespace std;

// Constants
const string WINDOWS_HOSTS = "C:\\Windows\\System32\\drivers\\etc\\hosts";
const string LINUX_HOSTS = "/etc/hosts";

// Methods
void appendFile(string file, string toAppend)
{
    ofstream outfile;
    outfile.open(file, ios_base::app);
    outfile << toAppend;
    outfile.close();
}

void blockMicrosoftTelemetry(string HOSTS, bool windows)
{
    appendFile(HOSTS, "\n# TelemetryBlocker (Block Microsoft Telemetry)\n");
    for (int i = 0; i < MicrosoftTelemetryEndpoints.size(); i++)
        appendFile(HOSTS, "0.0.0.0 " + MicrosoftTelemetryEndpoints[i] + "\n");

    if (windows) {
        system("sc config \"DiagTrack\" start=disabled");
        system("sc config \"diagnosticshub.standardcollector.service\" start=disabled");
        cout << "\nDisabled tracking services";
    }

    cout << "\nBlocked Windows Telemetry\n\n";
}

void blockGoogleTelemetry(string HOSTS) {
    appendFile(HOSTS, "\n# TelemetryBlocker (Ads & Tracking)\n");
    for (int i = 0; i < GoogleTrackingEndpoints.size(); i++)
        appendFile(HOSTS, "0.0.0.0 " + GoogleTrackingEndpoints[i] + "\n");
    cout << "\nBlocked Ads & Tracking Telemetry\n\n";
}

void blockMiscTrackersAndAds(string HOSTS) {
    appendFile(HOSTS, "\n# TelemetryBlocker (Misc Ads & Tracking)\n");
    for (int i = 0; i < MiscAdsAndTrackingEndpoints.size(); i++)
        appendFile(HOSTS, "0.0.0.0 " + MiscAdsAndTrackingEndpoints[i] + "\n");
    cout << "\nBlocked Misc ads & Trackers\n";
}

// Main loop
int main()
{
    bool isWindows = filesystem::exists(WINDOWS_HOSTS); // The bad operating system
    while (true) {
        int option;
        cout << "TelemetryBlocker\n\n1. Block Telemetry (Windows)\n2. Block Google Telemetry (Ads & Tracking)\n3. Block Misc Ads & Trackers \n\nChoose an option: ";
        cin >> option;

        if (!cin)
            break;

        switch (option) {
        case 1:
            blockMicrosoftTelemetry(isWindows ? WINDOWS_HOSTS : LINUX_HOSTS, isWindows);
            break;
        case 2:
            blockGoogleTelemetry(isWindows ? WINDOWS_HOSTS : LINUX_HOSTS);
            break;
        case 3:
            blockMiscTrackersAndAds(isWindows ? WINDOWS_HOSTS : LINUX_HOSTS);
            break;
        default:
            cout << "Invalid option.\n\n";
            break;
        }
    }

    return 0;
}
