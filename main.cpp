#include <iostream>
#include <string.h>
#include <list>

//#include "skin.h"
#include "player.h"
#include "world.h"

using namespace std;

/*

class World
    params: name, type

class Skin 
    params: color, width

class Player
    params: Id, nick, skin, health, state
*/
/***********************************************************/

// Global variables
std::list<class World*> world;
std::list<class Player*> list_players;
/***********************************************************/

class World *searchWorldByName(const string & name)
{
    class World *cur_world = nullptr;

    for (class World *w : world)
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
    const char *menu = "Menu: 1 - World, 2 - Player, 3 - Help, 4 - Exit";
    int n;

    enum CommandMain
    {
        CN_MenuWorld_E = 1,
        CN_MenuPlayer_E,
        CN_MenuHelp_E,
        CN_MenuExit_E
    };

    enum CommandWorld
    {
        CW_MenuWorldCreate_E = 1,
        CW_MenuWorldDelete_E,
        CW_MenuWorldPrintAllWorlds_E,
        CW_MenuWorldShowStatus_E,
        CW_MenuWorldAddPlayer_E,
        CW_MenuWorldDeletePlayer_E,
        CW_MenuWorldExit_E
    };

    enum CommandPlayer
    {
        CP_MenuPlayerCreate_E = 1,
        CP_MenuPlayerDelete_E,
        CP_MenuPlayerPrintAllPlayers_E,
        CP_MenuPlayerShowStatus_E,
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
                    cout << "Menu->World: 1 - Create, 2 - Delete, 3 - PrintAllWorlds, 4 - ShowStatus,"
                            " 5 - AddPlayer, 6 - DeletePlayer, 7 - Exit" << endl;
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
                            world.push_back(cur_world);
                    
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
                            world.remove(cur_world);
                            delete cur_world;

                        } break;

                        case CW_MenuWorldPrintAllWorlds_E:
                        {
                            n = 1;
                            for (class World *w : world)
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

                        case CW_MenuWorldAddPlayer_E:
                        {
                            bool add;
                            string name;
                            string nick;
                            class World *cur_world;
                            class Player *cur_player;

                            cout << "Menu->World->AddPlayer: input world name" << endl;
                            cin >> name;

                            // Check that World with this name exsist
                            cur_world = searchWorldByName(name);   
                            if (cur_world == nullptr)
                            {
                                cout << "World with this name doesn`t exist" << endl;
                                break;
                            }   

                            cout << "Menu->World->AddPlayer: input player nick" << endl;
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
                                add = cur_world->addPlayer(cur_player);

                                if (add == false)
                                {
                                    cout << "Player with this name already has added!" << endl;
                                }
                            }

                        } break;

                        case CW_MenuWorldDeletePlayer_E:
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
                                cur_world->deletePlayer(cur_player);
                        } break;

                        case CW_MenuWorldExit_E:
                        {
                            cout << "Exit" << endl;
                        } break;
                    }

                // Player
                case CN_MenuPlayer_E:
                    cout << "Menu->Player: 1 - Create, 2 - Delete, 3 - PrintAllPlayers, 4 - ShowStatus, 5 - Exit" << endl;
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
                            class World *cur_world;

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
                            cur_world = cur_player->getWorld();
                            if (cur_world != nullptr)
                            {
                                cur_world->deletePlayer(cur_player);
                            }
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

                        case CP_MenuPlayerExit_E:
                        {
                            cout << "Exit" << endl;

                        } break; 
                    }

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