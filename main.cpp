#include <iostream>
#include <string.h>
#include <fstream>
#include <list>

//#include "skin.h"
#include "player.h"
#include "world.h"

using namespace std;

#define END_MARKER_VALUE 373

/*

class World
    params: name, type

class Skin 
    params: color, width

class Player
    params: Id, nick, skin, health, state
*/
/***********************************************************/

// Change "world" to "list_worlds"
// Global variables
std::list<class World*> list_worlds;
std::list<class Player*> list_players;
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

class Player *searchPlayerByNick(const string & nick)
{
    class Player *cur_player = nullptr;

    /*
    cout << menu_name << " choose player by nick" << endl;
    cin >> nick;
    */

    for (class Player *p : list_players)
    {
        if (p->getNick() == nick)
        {
            cur_player = p;
            break;
        }
    }                            

    return cur_player;
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
    int user_inputX;
    int user_inputY;
    bool run = true;
    string name;
    int type;
    int Id;
    string nick;
    int color;
    int width;
    const char *menu = "Menu: 1 - World, 2 - Player, 3 - Load, 4 - Save, 5 - Help, 6 - Exit";
    string file_name = "Minecraft-01.bin";
    int n;
    int size;
    int end_marker;

    enum CommandMain
    {
        CN_MenuWorld_E = 1,
        CN_MenuPlayer_E,
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
        CW_MenuWorldJoinPlayer_E,
        CW_MenuWorldDisjoinPlayer_E,
        CW_MenuWorldShowMap_E,
        CW_MenuWorldSetTunaXY_E,
        CW_MenuWorldSetCarpXY_E,
        CW_MenuWorldExit_E
    };

    enum CommandPlayer
    {
        CP_MenuPlayerCreate_E = 1,
        CP_MenuPlayerDelete_E,
        CP_MenuPlayerPrintAllPlayers_E,
        CP_MenuPlayerShowStatus_E,
        CP_MenuPlayerSetPosition_E,
        CP_MenuPlayerExit_E
    };

    /* 
    Menu-> 1 World->  1.1 Create 
                      1.2 Delete
                      1.3 Show all
           2 Player-> 2.1 Create
                      2.2 Delete
                      2.3 Show all
           3 Help         
           4 Exit
    */

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
                            " 5 - JoinPlayer, 6 - DisjoinPlayer, 7 - ShowMap, 8 - SetTunaXY, 9 - SetCarpXY, 10 - Exit" << endl;
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

                        case CW_MenuWorldJoinPlayer_E:
                        {
                            bool add;
                            string name;
                            string nick;
                            class World *cur_world;
                            class Player *cur_player;

                            cout << "Menu->World->JoinPlayer: input world name" << endl;
                            cin >> name;

                            // Check that World with this name exsist
                            cur_world = searchWorldByName(name);   
                            if (cur_world == nullptr)
                            {
                                cout << "World with this name doesn`t exist" << endl;
                                break;
                            }   

                            cout << "Menu->World->JoinPlayer: input player nick" << endl;
                            cin >> nick;

                            // Check that Player with this nick exsist
                            cur_player = searchPlayerByNick(nick);
                            if (cur_player == nullptr)
                            {
                                cout << "Player with this nick doesn`t exist" << endl;
                                break;
                            }
                                
                            // Add Player to World
                            if (cur_world != nullptr && cur_player != nullptr)
                            {
                                add = cur_world->joinPlayer(cur_player);

                                if (add == false)
                                {
                                    cout << "Player with this name already has added!" << endl;
                                }
                            }

                        } break;

                        case CW_MenuWorldDisjoinPlayer_E:
                        {
                            string name;
                            string nick;
                            class World *cur_world;                                
                            class Player *cur_player;

                            cout << "Menu->World->PlayerDelete: input world name" << endl;
                            cin >> name;

                            // Check that World with this name exsist
                            cur_world = searchWorldByName(name);   
                            if (cur_world == nullptr)
                            {
                                cout << "World with this name doesn`t exist" << endl;
                                break;
                            }

                            cout << "Menu->World->PlayerDelete: input player nick" << endl;
                            cin >> nick;
                            
                            cur_player = searchPlayerByNick(nick);
                            if (cur_player == nullptr)
                            {
                                cout << "Player with this nick doesn`t exist" << endl;
                                break;
                            }

                            // Delete Player from World
                            if (cur_world != nullptr && cur_player != nullptr)
                            {
                                cur_world->disjoinPlayer(cur_player);
                                cur_player->setWorld(nullptr);
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

                        case CW_MenuWorldSetTunaXY_E:
                        {
                            string name;
                            class World *cur_world;

                            cout << "Menu->World->SetTunaXY: input world name" << endl;
                            cin >> name;

                            // Check that World with this name exsist
                            cur_world = searchWorldByName(name);
                            if (cur_world == nullptr)
                            {
                                cout << "World with this name doesn`t exist" << endl;
                                break;
                            }

                            // Get X and Y from user for Tuna
                            cout << "Input value for X for Tuna:" << endl;
                            user_inputX = getValueInt(0, WORLD_MAP_SIZE);

                            cout << "Input value for Y for Tuna:" << endl;
                            user_inputY = getValueInt(0, WORLD_MAP_SIZE);

                            // Set X and Y for Tuna
                            cur_world->setTunaXY(user_inputX, user_inputY);
                        } break;

                        case CW_MenuWorldSetCarpXY_E:
                        {

                        } break;

                        case CW_MenuWorldExit_E:
                        {
                            cout << "Exit" << endl;
                        } break;
                    }
                } break;

                // Player
                case CN_MenuPlayer_E:
                {
                    cout << "Menu->Player: 1 - Create, 2 - Delete, 3 - PrintAllPlayers, 4 - ShowStatus, 5 - SetPosition, 6 - Exit" << endl;
                    user_input = getValueInt(CP_MenuPlayerCreate_E, CP_MenuPlayerExit_E);
                    switch (user_input)
                    {
                        case CP_MenuPlayerCreate_E:
                        {
                            string nick;
                            class Player *cur_player;

                            cout << "Menu->Player->Create: input Id, nick, skin's color and width " << endl;
                            cin >> Id >> nick >> color >> width;

                            // Check that Player with this nick doesn`t exsist
                            cur_player = searchPlayerByNick(nick);   
                            if (cur_player != nullptr)
                            {
                                cout << "Can`t create new Player with this nick" << endl;
                                break;
                            }
                            
                            // Creating new Player
                            cur_player = new Player(Id, nick, (Skin::Colors)color, (Skin::Width)width);      
                            list_players.push_back(cur_player);                              
                        } break;

                        case CP_MenuPlayerDelete_E:
                        {
                            string nick;
                            class Player *cur_player;

                            cout << "Menu->Player->Delete: input player`s nick" << endl;
                            cin >> nick;

                            // Check that Player with this nick exsist
                            cur_player = searchPlayerByNick(nick);   
                            if (cur_player == nullptr)
                            {
                                cout << "Can`t delete Player with this nick" << endl;
                                break;
                            }

                            // Deleting player
                            list_players.remove(cur_player);
                            delete cur_player;

                        } break;

                        case CP_MenuPlayerPrintAllPlayers_E:
                        {    
                            n = 1;
                            for (class Player *p : list_players)
                                cout << n++ << ". " << p->getNick() << endl;

                        } break;

                        case CP_MenuPlayerShowStatus_E:
                        {
                            string nick;
                            class Player *cur_player;

                            cout << "Menu->Player->ShowStatus: input nick" << endl;
                            cin >> nick;

                            // Check that Player with this nick exsist
                            cur_player = searchPlayerByNick(nick);   
                            if (cur_player == nullptr)
                            {                               
                                cout << "Player with this nick doesn`t exist" << endl;
                                break;
                            }

                            // Show status
                            cur_player->showPlayerStatus();
                            
                        } break;

                        case CP_MenuPlayerSetPosition_E:
                        {
                            float x, y;
                            string nick;
                            class Player *cur_player;

                            cout << "Menu->Player->SetPosition: input player nick" << endl;
                            cin >> nick;

                            // Check that Player with this nick exsist
                            cur_player = searchPlayerByNick(nick);
                            if (cur_player == nullptr)
                            {
                                cout << "Player with this nick doesn`t exist" << endl;
                                break;
                            }

                            cout << "Input position of player(x, y)" << endl;
                            cin >> x >> y;
                            cur_player->setXY(x, y);
                        } break;

                        case CP_MenuPlayerExit_E:
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
                    class Player * cur_player;

                    // Check old objects worlds and players
                    if (list_worlds.size() != 0 || list_players.size() != 0)
                    {
                        cout << "List of worlds or players aren't empty. Do you want to delete them?[Y/N]" << endl;
                        if (getValueYesOrNo())
                        {
                            // Deletes all worlds and players
                            
                            for (class World *cur_world : list_worlds)
                            {
                                // Deleting World
                                delete cur_world;
                            }
                            list_worlds.clear();

                            for (class Player *cur_player : list_players)
                            {
                                // Deleting Player
                                delete cur_player;
                            }
                            list_players.clear();
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

                        // 3 - Loading amount of players in the list
                        file.read((char *)&size, sizeof(size));

                        // 4 - Loading every Player's instance from file
                        for (; size > 0; size--)
                        {
                            cur_player = new Player();
                            cur_player->load(file, list_worlds);
                            list_players.push_back(cur_player);
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

                        // 3 - Save amount of players in the list
                        size = list_players.size();
                         
                        file.write((const char *)&size, sizeof(size));

                        // 4 - Saving every Player's instance to file
                        for (class Player *p : list_players)
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