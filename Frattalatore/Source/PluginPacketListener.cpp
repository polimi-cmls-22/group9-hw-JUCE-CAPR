#include "PluginPacketListener.h"
#include <juce_core/system/juce_PlatformDefs.h>

void  PluginPacketListener::ProcessMessage(const osc::ReceivedMessage& m,
        const IpEndpointName& remoteEndpoint)
    {
        (void)remoteEndpoint; // suppress unused parameter warning

        try {
            // example of parsing single messages. osc::OsckPacketListener
            // handles the bundle traversal.

            if (std::strcmp(m.AddressPattern(), "/test1") == 0) {
                // example #1 -- argument stream interface
                osc::ReceivedMessageArgumentStream args = m.ArgumentStream();
                bool a1;
                osc::int32 a2;
                float a3;
                const char* a4;
                args >> a1 >> a2 >> a3 >> a4 >> osc::EndMessage;

                DBG(args);
                    //<< a1 << " " << a2 << " " << a3 << " " << a4 << "\n";

            }
            else if (std::strcmp(m.AddressPattern(), "/test2") == 0) {
                // example #2 -- argument iterator interface, supports
                // reflection for overloaded messages (eg you can call 
                // (*arg)->IsBool() to check if a bool was passed etc).
                osc::ReceivedMessage::const_iterator arg = m.ArgumentsBegin();
                bool a1 = (arg++)->AsBool();
                int a2 = (arg++)->AsInt32();
                float a3 = (arg++)->AsFloat();
                const char* a4 = (arg++)->AsString();
                if (arg != m.ArgumentsEnd())
                    throw osc::ExcessArgumentException();

                DBG(args);
                   // << a1 << " " << a2 << " " << a3 << " " << a4 << "\n";
            }
        }
        catch (osc::Exception& e) {
            // any parsing errors such as unexpected argument types, or 
            // missing arguments get thrown as exceptions.
            DBG("error while parsing message: ");
                //<< m.AddressPattern() << ": " << e.what() << "\n";
        }
    }