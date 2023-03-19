#include <iostream>
#include <string.h>
#include <fstream>
#include <list>

//#include "skin.h"
#include "fisherman.h"
#include "location.h"

using namespace std;

#define END_MARKER_VALUE 373

/*

class Location
    params: name, type

class Skin 
    params: color, width

class Fisherman
    params: Id, nick, skin, health, state
*/
/***********************************************************/

// Change "Location" to "list_Locations"
// Global variables
std::list<class Location*> list_Locations;
std::list<class Fisherman*> list_fishermen;
/***********************************************************/

class Location *searchLocationByName(const string & name)
{
    class Location *cur_Location = nullptr;

    for (class Location *w : list_Locations)
    {
        if (w->getName() == name)
        {
            cur_Location = w;
            break;      
        }
    }                            

    return cur_Location;
}

class Fisherman *searchFishermanByNick(const string &nick)
{
    class Fisherman *cur_fisherman = nullptr;

    /*
    cout << menu_name << " choose Fisherman by nick" << endl;
    cin >> nick;
    */

    for (class Fisherman *p : list_fishermen)
    {
        if (p->getNick() == nick)
        {
            cur_fisherman = p;
            break;
        }
    }

    return cur_fisherman;
}

int getValueInt(int diapason_1, int diapason_2)
{
    int input;

    while (true)
    {
        cin >> input;

        if (cin.fail())
        {
            cin.clear();
            cin.ignore();
            cout << "Wrong input! Try again" << endl;
            continue;
        }  
        else 
        {  
            if ((diapason_1 > diapason_2 && (input >= diapason_2 && input <= diapason_1)) || 
                                            (input >= diapason_1 && input <= diapason_2))
            {
                cin.ignore(32767, '\n');
                return input;
            }
            else 
            {
                cout << "Wrong input! Try again" << endl;
                continue;
            }
        }
    }

    return 0;
}

bool getValueYesOrNo(void)
{
    char input;

    while (true)
    {
        cin >> input;

        if (cin.fail())
        {
            cin.clear();
            cin.ignore();
            cout << "Wrong input! Try again" << endl;
            continue;
        }
        else
        {
            if (input == 'Y' || input == 'N')
            {
                cin.ignore(32767, '\n');
                if (input == 'Y')
                    return true;
                else
                    return false;
            }
            else
            {
                cout << "Wrong input! Try again" << endl;
                continue;
            }
        }
    }

    return false;
}
/***********************************************************/

int main()
{   
    int user_input = 0;
    bool run = true;
    string name;
    int type;
    int Id;
    string nick;
    int color;
    int width;
    const char *menu = "Menu: 1 - Location, 2 - Fisherman, 3 - Load, 4 - Save, 5 - Help, 6 - Exit";
    string file_name = "fisherman-01.bin";
    int n;
    int size;
    int end_marker;

    enum CommandMain
    {
        CN_MenuLocation_E = 1,
        CN_MenuFisherman_E,
        CN_MenuLoad_E,
        CN_MenuSave_E,
        CN_MenuHelp_E,
        CN_MenuExit_E
    };

    enum CommandLocation
    {
        CW_MenuLocationCreate_E = 1,
        CW_MenuLocationDelete_E,
        CW_MenuLocationPrintAllLocations_E,
        CW_MenuLocationShowStatus_E,
        CW_MenuLocationJoinFisherman_E,
        CW_MenuLocationDisjoinFisherman_E,
        CW_MenuLocationShowMap_E,
        CW_MenuLocationPlayRound_E,
        CW_MenuLocationExit_E
    };

    enum CommandFisherman
    {
        CP_MenuFishermanCreate_E = 1,
        CP_MenuFishermanDelete_E,
        CP_MenuFishermanPrintAllFishermen_E,
        CP_MenuFishermanShowStatus_E,
        CP_MenuFishermanSetPosition_E,
        CP_MenuFishermanExit_E
    };

    cout << menu << endl;

    while (run)
    {
        cout << "Choose one of Menu item: " << endl;
        user_input = getValueInt(CN_MenuLocation_E, CN_MenuExit_E);   

            switch (user_input)
            {
                // Location
                case CN_MenuLocation_E:
                {
                    cout << "Menu->Location: 1 - Create, 2 - Delete, 3 - PrintAllLocations, 4 - ShowStatus,"
                            " 5 - JoinFisherman, 6 - DisjoinFisherman, 7 - ShowMap, 8 - PlayRound, 9 - Exit" << endl;
                    user_input = getValueInt(CW_MenuLocationCreate_E, CW_MenuLocationExit_E);
                    switch (user_input)
                    {
                        case CW_MenuLocationCreate_E:
                        {
                            string name;
                            class Location *cur_location;

                            cout << "Menu->Location->Create: input name and type[1 - lake, 2 - river, 3 - sea]" << endl;
                            cin >> name >> type;

                            // Check that Location with this name doesn`t exsist
                            cur_location = searchLocationByName(name);
                            if (cur_location != nullptr)
                            {
                                cout << "Can`t create new Location with this name" << endl;
                                break;
                            }

                            // Creating new Location
                            cur_location = new Location(name, (Location::LocationType)type);
                            list_Locations.push_back(cur_location);
                            
                        } break;

                        case CW_MenuLocationDelete_E:
                        {   
                            string name;
                            class Location *cur_Location;

                            cout << "Menu->Location->Delete: input Location name" << endl;
                            cin >> name;

                            // Check that Location with this name exsist
                            cur_Location = searchLocationByName(name);   
                            if (cur_Location == nullptr)
                            {
                                cout << "Can`t delete Location with this name" << endl;
                                break;
                            }

                            // Deleting Location
                            list_Locations.remove(cur_Location);
                            delete cur_Location;

                        } break;

                        case CW_MenuLocationPrintAllLocations_E:
                        {
                            n = 1;
                            for (class Location *w : list_Locations)
                                cout << n++ << ". " << w->getName() << endl;

                        } break;

                        case CW_MenuLocationShowStatus_E:
                        {
                            string name;
                            class Location *cur_location;

                            cout << "Menu->Location->ShowStatus: input name" << endl;
                            cin >> name;

                            // Check that Location with this name exsist
                            cur_location = searchLocationByName(name);   
                            if (cur_location == nullptr)
                            {                               
                                cout << "Location with this name doesn`t exist" << endl;
                                break;
                            }

                            // Show Location status
                            cur_location->showLocationStatus();

                        } break;

                        case CW_MenuLocationJoinFisherman_E:
                        {
                            bool add;
                            string name;
                            string nick;
                            class Location *cur_location;
                            class Fisherman *cur_fisherman;

                            cout << "Menu->Location->JoinFisherman: input Location name" << endl;
                            cin >> name;

                            // Check that Location with this name exsist
                            cur_location = searchLocationByName(name);   
                            if (cur_location == nullptr)
                            {
                                cout << "Location with this name doesn`t exist" << endl;
                                break;
                            }

                            cout << "Menu->Location->JoinFisherman: input fisherman nick" << endl;
                            cin >> nick;

                            // Check that Fisherman with this nick exsist
                            cur_fisherman = searchFishermanByNick(nick);
                            if (cur_fisherman == nullptr)
                            {
                                cout << "Fisherman with this nick doesn`t exist" << endl;
                                break;
                            }

                            // Add Fisherman to Location
                            if (cur_location != nullptr && cur_fisherman != nullptr)
                            {
                                add = cur_location->joinFisherman(cur_fisherman);

                                if (add == false)
                                {
                                    cout << "Fisherman with this name already has added!" << endl;
                                }
                            }

                        } break;

                        case CW_MenuLocationDisjoinFisherman_E:
                        {
                            string name;
                            string nick;
                            class Location *cur_Location;
                            class Fisherman *cur_fisherman;

                            cout << "Menu->Location->FishermanDelete: input Location name" << endl;
                            cin >> name;

                            // Check that Location with this name exsist
                            cur_Location = searchLocationByName(name);   
                            if (cur_Location == nullptr)
                            {
                                cout << "Location with this name doesn`t exist" << endl;
                                break;
                            }

                            cout << "Menu->Location->FishermanDelete: input fisherman nick" << endl;
                            cin >> nick;

                            cur_fisherman = searchFishermanByNick(nick);
                            if (cur_fisherman == nullptr)
                            {
                                cout << "Fisherman with this nick doesn`t exist" << endl;
                                break;
                            }

                            // Delete Fisherman from Location
                            if (cur_Location != nullptr && cur_fisherman != nullptr)
                            {
                                cur_Location->disjoinFisherman(cur_fisherman);
                                cur_fisherman->setLocation(nullptr);
                            }
                        } break;

                        case CW_MenuLocationShowMap_E:
                        {
                            string name;
                            class Location *cur_Location;

                            cout << "Menu->Location->ShowMap: input Location name" << endl;
                            cin >> name;

                            // Check that Location with this name exsist
                            cur_Location = searchLocationByName(name);
                            if (cur_Location == nullptr)
                            {
                                cout << "Location with this name doesn`t exist" << endl;
                                break;
                            }

                            cur_Location->showMap();
                        } break;

                        case CW_MenuLocationPlayRound_E:
                        {
                            string name;
                            class Location *cur_Location;
                            int index;

                            cout << "Menu->Location->PlayRound: input Location name" << endl;
                            cin >> name;

                            // Check that Location with this name exsist
                            cur_Location = searchLocationByName(name);
                            if (cur_Location == nullptr)
                            {
                                cout << "Location with this name doesn`t exist" << endl;
                                break;
                            }

                            for (index = 0; index < 43; index++)
                            {
                                cur_Location->playRound();
                            }
                        } break;
                    }
                } break;

                // Fisherman
                case CN_MenuFisherman_E:
                {
                            cout << "Menu->Fisherman: 1 - Create, 2 - Delete, 3 - PrintAllFishermen, 4 - ShowStatus, 5 - SetPosition, 6 - Exit" << endl;
                            user_input = getValueInt(CP_MenuFishermanCreate_E, CP_MenuFishermanExit_E);
                            switch (user_input)
                            {
                            case CP_MenuFishermanCreate_E:
                            {
                                    string nick;
                                    class Fisherman *cur_fisherman;

                                    cout << "Menu->Fisherman->Create: input Id, nick, skin's color and width " << endl;
                                    cin >> Id >> nick >> color >> width;

                                    // Check that Fisherman with this nick doesn`t exsist
                                    cur_fisherman = searchFishermanByNick(nick);
                                    if (cur_fisherman != nullptr)
                                    {
                                        cout << "Can`t create new Fisherman with this nick" << endl;
                                        break;
                                    }

                                    // Creating new Fisherman
                                    cur_fisherman = new Fisherman(Id, nick, (Skin::Colors)color, (Skin::Width)width);
                                    list_fishermen.push_back(cur_fisherman);
                        } break;

                        case CP_MenuFishermanDelete_E:
                        {
                            string nick;
                            class Fisherman *cur_fisherman;

                            cout << "Menu->Fisherman->Delete: input fisherman`s nick" << endl;
                            cin >> nick;

                            // Check that Fisherman with this nick exsist
                            cur_fisherman = searchFishermanByNick(nick);
                            if (cur_fisherman == nullptr)
                            {
                                cout << "Can`t delete Fisherman with this nick" << endl;
                                break;
                            }

                            // Deleting fisherman
                            list_fishermen.remove(cur_fisherman);
                            delete cur_fisherman;

                        } break;

                        case CP_MenuFishermanPrintAllFishermen_E:
                        {    
                            n = 1;
                            for (class Fisherman *p : list_fishermen)
                            {
                                cout << n++ << ". " << p->getNick() << " - f:";
                                p->showFish();
                            }
                        } break;

                        case CP_MenuFishermanShowStatus_E:
                        {
                            string nick;
                            class Fisherman *cur_fisherman;

                            cout << "Menu->Fisherman->ShowStatus: input nick" << endl;
                            cin >> nick;

                            // Check that Fisherman with this nick exsist
                            cur_fisherman = searchFishermanByNick(nick);
                            if (cur_fisherman == nullptr)
                            {
                                cout << "Fisherman with this nick doesn`t exist" << endl;
                                break;
                            }

                            // Show status
                            cur_fisherman->showFishermanStatus();
                        } break;

                        case CP_MenuFishermanSetPosition_E:
                        {
                            float x, y;
                            string nick;
                            class Fisherman *cur_fisherman;

                            cout << "Menu->Fisherman->SetPosition: input fisherman nick" << endl;
                            cin >> nick;

                            // Check that Fisherman with this nick exsist
                            cur_fisherman = searchFishermanByNick(nick);
                            if (cur_fisherman == nullptr)
                            {
                                cout << "Fisherman with this nick doesn`t exist" << endl;
                                break;
                            }

                            cout << "Input position of fisherman(x, y)" << endl;
                            cin >> x >> y;
                            cur_fisherman->setXY(x, y);
                        } break;

                        case CP_MenuFishermanExit_E:
                        {
                            cout << "Exit" << endl;

                        } break;
                    }
                } break;

                // Load
                case CN_MenuLoad_E:
                {
                    std::ifstream file;
                    class Location * cur_Location;
                    class Fisherman *cur_fisherman;

                    // Check old objects Locations and fishermen
                    if (list_Locations.size() != 0 || list_fishermen.size() != 0)
                    {
                        cout << "List of Locations or fishermen aren't empty. Do you want to delete them?[Y/N]" << endl;
                        if (getValueYesOrNo())
                        {
                            // Deletes all Locations and fishermen
                            
                            for (class Location *cur_Location : list_Locations)
                            {
                                // Deleting Location
                                delete cur_Location;
                            }
                            list_Locations.clear();

                            for (class Fisherman *cur_fisherman : list_fishermen)
                            {
                                // Deleting Fisherman
                                delete cur_fisherman;
                            }
                            list_fishermen.clear();
                        }
                        else 
                        {
                            break;
                        }
                    }

                    file.open(file_name, ios_base::in | ios_base::binary);

                    if (file.is_open())
                    {
                        // 1 - Loading amount of instance of Location in the list
                        file.read((char *)&size, sizeof(size));

                        // 2 - Loading every Location's instnce from the file
                        for (; size > 0; size--)
                        {
                            cur_Location = new Location();
                            cur_Location->load(file);
                            list_Locations.push_back(cur_Location);
                        }

                        // 3 - Loading amount of fishermen in the list
                        file.read((char *)&size, sizeof(size));

                        // 4 - Loading every Fisherman's instance from file
                        for (; size > 0; size--)
                        {
                            cur_fisherman = new Fisherman();
                            cur_fisherman->load(file, list_Locations);
                            list_fishermen.push_back(cur_fisherman);
                        }

                        // 5 - Loading the end marker from the file
                        file.read((char *)&end_marker, sizeof(end_marker));
                        file.close();

                        if (end_marker == END_MARKER_VALUE)
                        {
                            cout << "Data was load from file: " << file_name << " successfully" << endl;
                        }
                        else
                        {
                            cout << "Data was load from file: " << file_name << " wrong" << endl;
                        } 
                    }
                    else
                    {
                        cout << "File " << file_name << " absent" << endl;
                    }

                } break;

                // Save
                case CN_MenuSave_E:
                {
                    std::ofstream file;

                    file.open(file_name, ios_base::out | ios_base::binary | ios_base::trunc);

                    if (file.is_open())
                    {
                        // 1 - Saving amount of instance of Location in the list
                        size = list_Locations.size();
                        end_marker = END_MARKER_VALUE;

                        file.write((const char *)&size, sizeof(size));

                        // 2 - Saving every Location's instance to file
                        for (class Location *w : list_Locations)
                        {
                            w->save(file); 
                        }

                        // 3 - Save amount of fishermen in the list
                        size = list_fishermen.size();
                         
                        file.write((const char *)&size, sizeof(size));

                        // 4 - Saving every Fisherman's instance to file
                        for (class Fisherman *p : list_fishermen)
                        {
                            p->save(file);
                        }

                        // 5 - Saving the end marker to the file
                        file.write((const char *)&end_marker, sizeof(end_marker));

                        file.close();

                        cout << "Data was saved to file: " << file_name << endl;
                    }
                } break;

                // Help
                case CN_MenuHelp_E:
                {
                    cout << menu << endl;

                } break;

                // Exit
                case CN_MenuExit_E: 
                {                   
                    cout << "Exit" << endl;
                    run = false;
                    
                } break;
            }
    }

    return 0;
}