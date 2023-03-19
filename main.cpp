#include <iostream>
#include <string.h>
#include <fstream>
#include <list>

//#include "skin.h"
#include "fisherman.h"
#include "world.h"

using namespace std;

#define END_MARKER_VALUE 373

/*

class World
    params: name, type

class Skin 
    params: color, width

class Fisherman
    params: Id, nick, skin, health, state
*/
/***********************************************************/

// Change "world" to "list_worlds"
// Global variables
std::list<class World*> list_worlds;
std::list<class Fisherman*> list_fishermen;
/***********************************************************/

class World *searchWorldByName(const string & name)
{
    class World *cur_world = nullptr;

    for (class World *w : list_worlds)
    {
        if (w->getName() == name)
        {
            cur_world = w;
            break;      
        }
    }                            

    return cur_world;
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
    const char *menu = "Menu: 1 - World, 2 - Fisherman, 3 - Load, 4 - Save, 5 - Help, 6 - Exit";
    string file_name = "fisherman-01.bin";
    int n;
    int size;
    int end_marker;

    enum CommandMain
    {
        CN_MenuWorld_E = 1,
        CN_MenuFisherman_E,
        CN_MenuLoad_E,
        CN_MenuSave_E,
        CN_MenuHelp_E,
        CN_MenuExit_E
    };

    enum CommandWorld
    {
        CW_MenuWorldCreate_E = 1,
        CW_MenuWorldDelete_E,
        CW_MenuWorldPrintAllWorlds_E,
        CW_MenuWorldShowStatus_E,
        CW_MenuWorldJoinFisherman_E,
        CW_MenuWorldDisjoinFisherman_E,
        CW_MenuWorldShowMap_E,
        CW_MenuWorldPlayRound_E,
        CW_MenuWorldExit_E
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
        user_input = getValueInt(CN_MenuWorld_E, CN_MenuExit_E);   

            switch (user_input)
            {
                // World
                case CN_MenuWorld_E:
                {
                    cout << "Menu->World: 1 - Create, 2 - Delete, 3 - PrintAllWorlds, 4 - ShowStatus,"
                            " 5 - JoinFisherman, 6 - DisjoinFisherman, 7 - ShowMap, 8 - PlayRound, 9 - Exit" << endl;
                    user_input = getValueInt(CW_MenuWorldCreate_E, CW_MenuWorldExit_E);
                    switch (user_input)
                    {
                    case CW_MenuWorldCreate_E:
                    {
                        string name;
                        class World *cur_world;

                        cout << "Menu->World->Create: input name and type" << endl;
                        cin >> name >> type;

                        // Check that World with this name doesn`t exsist
                        cur_world = searchWorldByName(name);
                        if (cur_world != nullptr)
                        {
                            cout << "Can`t create new World with this name" << endl;
                            break;
                        }

                        // Creating new World
                        cur_world = new World(name, (World::Type)type);
                        list_worlds.push_back(cur_world);
                            
                                } break;

                                case CW_MenuWorldDelete_E:
                                {   
                                    string name;
                                    class World *cur_world;

                                    cout << "Menu->World->Delete: input world name" << endl;
                                    cin >> name;

                                    // Check that World with this name exsist
                                    cur_world = searchWorldByName(name);   
                                    if (cur_world == nullptr)
                                    {
                                        cout << "Can`t delete World with this name" << endl;
                                        break;
                                    }

                                    // Deleting World
                                    list_worlds.remove(cur_world);
                                    delete cur_world;

                                } break;

                                case CW_MenuWorldPrintAllWorlds_E:
                                {
                                    n = 1;
                                    for (class World *w : list_worlds)
                                        cout << n++ << ". " << w->getName() << endl;

                                } break;

                                case CW_MenuWorldShowStatus_E:
                                {
                                    string name;
                                    class World *cur_world;

                                    cout << "Menu->World->ShowStatus: input name" << endl;
                                    cin >> name;

                                    // Check that World with this name exsist
                                    cur_world = searchWorldByName(name);   
                                    if (cur_world == nullptr)
                                    {                               
                                        cout << "World with this name doesn`t exist" << endl;
                                        break;
                                    }

                                    // Show World status
                                    cur_world->showWorldStatus();

                                } break;

                                case CW_MenuWorldJoinFisherman_E:
                                {
                                    bool add;
                                    string name;
                                    string nick;
                                    class World *cur_world;
                                    class Fisherman *cur_fisherman;

                                    cout << "Menu->World->JoinFisherman: input world name" << endl;
                                    cin >> name;

                                    // Check that World with this name exsist
                                    cur_world = searchWorldByName(name);   
                                    if (cur_world == nullptr)
                                    {
                                        cout << "World with this name doesn`t exist" << endl;
                                        break;
                                    }

                                    cout << "Menu->World->JoinFisherman: input fisherman nick" << endl;
                                    cin >> nick;

                                    // Check that Fisherman with this nick exsist
                                    cur_fisherman = searchFishermanByNick(nick);
                                    if (cur_fisherman == nullptr)
                                    {
                                        cout << "Fisherman with this nick doesn`t exist" << endl;
                                        break;
                                    }

                                    // Add Fisherman to World
                                    if (cur_world != nullptr && cur_fisherman != nullptr)
                                    {
                                        add = cur_world->joinFisherman(cur_fisherman);

                                        if (add == false)
                                        {
                                            cout << "Fisherman with this name already has added!" << endl;
                                        }
                                    }

                                } break;

                                case CW_MenuWorldDisjoinFisherman_E:
                                {
                                    string name;
                                    string nick;
                                    class World *cur_world;
                                    class Fisherman *cur_fisherman;

                                    cout << "Menu->World->FishermanDelete: input world name" << endl;
                                    cin >> name;

                                    // Check that World with this name exsist
                                    cur_world = searchWorldByName(name);   
                                    if (cur_world == nullptr)
                                    {
                                        cout << "World with this name doesn`t exist" << endl;
                                        break;
                                    }

                                    cout << "Menu->World->FishermanDelete: input fisherman nick" << endl;
                                    cin >> nick;

                                    cur_fisherman = searchFishermanByNick(nick);
                                    if (cur_fisherman == nullptr)
                                    {
                                        cout << "Fisherman with this nick doesn`t exist" << endl;
                                        break;
                                    }

                                    // Delete Fisherman from World
                                    if (cur_world != nullptr && cur_fisherman != nullptr)
                                    {
                                        cur_world->disjoinFisherman(cur_fisherman);
                                        cur_fisherman->setWorld(nullptr);
                                    }
                                } break;

                                case CW_MenuWorldShowMap_E:
                                {
                                    string name;
                                    class World *cur_world;

                                    cout << "Menu->World->ShowMap: input world name" << endl;
                                    cin >> name;

                                    // Check that World with this name exsist
                                    cur_world = searchWorldByName(name);
                                    if (cur_world == nullptr)
                                    {
                                        cout << "World with this name doesn`t exist" << endl;
                                        break;
                                    }

                                    cur_world->showMap();
                                } break;

                                case CW_MenuWorldPlayRound_E:
                                {
                                    string name;
                                    class World *cur_world;
                                    int index;

                                    cout << "Menu->World->PlayRound: input world name" << endl;
                                    cin >> name;

                                    // Check that World with this name exsist
                                    cur_world = searchWorldByName(name);
                                    if (cur_world == nullptr)
                                    {
                                        cout << "World with this name doesn`t exist" << endl;
                                        break;
                                    }

                                    for (index = 0; index < 43; index++)
                                    {
                                        cur_world->playRound();
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
                    class World * cur_world;
                    class Fisherman *cur_fisherman;

                    // Check old objects worlds and fishermen
                    if (list_worlds.size() != 0 || list_fishermen.size() != 0)
                    {
                        cout << "List of worlds or fishermen aren't empty. Do you want to delete them?[Y/N]" << endl;
                        if (getValueYesOrNo())
                        {
                            // Deletes all worlds and fishermen
                            
                            for (class World *cur_world : list_worlds)
                            {
                                // Deleting World
                                delete cur_world;
                            }
                            list_worlds.clear();

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
                        // 1 - Loading amount of instance of World in the list
                        file.read((char *)&size, sizeof(size));

                        // 2 - Loading every World's instnce from the file
                        for (; size > 0; size--)
                        {
                            cur_world = new World();
                            cur_world->load(file);
                            list_worlds.push_back(cur_world);
                        }

                        // 3 - Loading amount of fishermen in the list
                        file.read((char *)&size, sizeof(size));

                        // 4 - Loading every Fisherman's instance from file
                        for (; size > 0; size--)
                        {
                            cur_fisherman = new Fisherman();
                            cur_fisherman->load(file, list_worlds);
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
                        // 1 - Saving amount of instance of World in the list
                        size = list_worlds.size();
                        end_marker = END_MARKER_VALUE;

                        file.write((const char *)&size, sizeof(size));

                        // 2 - Saving every World's instance to file
                        for (class World *w : list_worlds)
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