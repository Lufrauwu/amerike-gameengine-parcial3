#include "CommonHeaders.hh"
#include "Player.hh"
#include "Animation.hh"
#include "TileGroup.hh"


sf::CircleShape* circle{new sf::CircleShape()};

TextObject* textObj1{new TextObject(ASSETS_FONT_ARCADECLASSIC, 14, sf::Color::White, sf::Text::Bold)};

int x;
int y;
sf::Clock* gameClock{new sf::Clock()};
float deltaTime{};
Player* player1{};
GameObject* Walls[30]{};
GameObject* Invisible{};
GameObject* chest1{};
GameObject* light1{};
Animation* idleAnimation{new Animation()};
Animation* runAnimation{new Animation()};

TileGroup* tileGroup{};
Tile* tile1{};

uint32 flags{};
    //flags += b2Draw::e_aabbBit;
    //flags += b2Draw::e_shapeBit;
    //flags += b2Draw::e_centerOfMassBit;
    //flags += b2Draw::e_pairBit;
    //flags += b2Draw::e_jointBit;

Animation* lightIdle{};

Game::Game()
{
  window = new sf::RenderWindow(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), GAME_NAME);
  event = new sf::Event();
  gravity = new b2Vec2(0.f, 0.f);
  world = new b2World(*gravity);
  drawPhysics = new DrawPhysics(window);
  gameObjects = new std::vector<GameObject*>();
  gameObjectsDeleteList = new std::vector<GameObject*>();

  player1 = new Player(ASSETS_SPRITES, 4.f, 16, 16, 0, 5, 500, 200, 200.f, b2BodyType::b2_dynamicBody, world, window);
  player1->SetTagName("Player");
  chest1 = new GameObject(ASSETS_SPRITES, 4.f, 16, 16, 6, 1, 900, 900, b2BodyType::b2_staticBody, world, window);
  chest1->SetTagName("chest");
  light1 = new GameObject(ASSETS_SPRITES, 4.f, 16, 16, 6, 3, 2000, 2000, b2BodyType::b2_staticBody, world, window);
  light1->SetTagName("light");
  Invisible=new GameObject(ASSETS_TILES,4.f, 1080, 8, 0, 0, 0, 1080, b2BodyType::b2_staticBody, world, window);
  Invisible->SetTagName("inv1");
  Invisible=new GameObject(ASSETS_TILES,4.f, 8, 1080, 0, 0, 0, 0, b2BodyType::b2_staticBody, world, window);
  Invisible->SetTagName("inv2");
  Invisible=new GameObject(ASSETS_TILES,4.f, 8, 1080, 0, 0, 1080, 0, b2BodyType::b2_staticBody, world, window);
  Invisible->SetTagName("inv3");

  Invisible=new GameObject(ASSETS_TILES,4.f, 300, 16, 0, 0, 260, 260, b2BodyType::b2_staticBody, world, window);
  Invisible->SetTagName("inv5");
  Invisible=new GameObject(ASSETS_TILES,4.f, 16, 50, 0, 0, 600, 330, b2BodyType::b2_staticBody, world, window);
  Invisible->SetTagName("inv6");
  Invisible=new GameObject(ASSETS_TILES,4.f, 16, 75, 0, 0, 960, 380, b2BodyType::b2_staticBody, world, window);
  Invisible->SetTagName("inv7");
  Invisible=new GameObject(ASSETS_TILES,4.f, 75, 16, 0, 0, 842, 560, b2BodyType::b2_staticBody, world, window);
  Invisible->SetTagName("inv8");
  Invisible=new GameObject(ASSETS_TILES,4.f, 16, 75, 0, 0, 725, 675, b2BodyType::b2_staticBody, world, window);
  Invisible->SetTagName("inv9");
  Invisible=new GameObject(ASSETS_TILES,4.f, 100, 16, 0, 0, 900, 790, b2BodyType::b2_staticBody, world, window);
  Invisible->SetTagName("inv10");
  Invisible=new GameObject(ASSETS_TILES,4.f, 16, 50, 0, 0, 575, 660, b2BodyType::b2_staticBody, world, window);
  Invisible->SetTagName("inv11");
  Invisible=new GameObject(ASSETS_TILES,4.f, 75, 16, 0, 0, 460, 730, b2BodyType::b2_staticBody, world, window);
  Invisible->SetTagName("inv12");
  Invisible=new GameObject(ASSETS_TILES,4.f, 16, 100, 0, 0, 340, 560, b2BodyType::b2_staticBody, world, window);
  Invisible->SetTagName("inv13");
  Invisible=new GameObject(ASSETS_TILES,4.f, 65, 16, 0, 0, 220, 570, b2BodyType::b2_staticBody, world, window);
  Invisible->SetTagName("inv14");
  Invisible=new GameObject(ASSETS_TILES,4.f, 130, 16, 0, 0, 450, 860, b2BodyType::b2_staticBody, world, window);
  Invisible->SetTagName("inv15");
  Invisible=new GameObject(ASSETS_TILES,4.f, 16, 75, 0, 0, 160, 730, b2BodyType::b2_staticBody, world, window);
  Invisible->SetTagName("inv16");
  tileGroup = new TileGroup(window, 12, 12, ASSETS_MAPS,5.56f, 16, 16, ASSETS_TILES);
  for(int i=0;i<10;i++)
  {
    Walls[i]=new GameObject(ASSETS_TILES, 4.f, 32, 32, 0, 0, x, 0, b2BodyType::b2_staticBody, world, window);
    Walls[i]->SetTagName("wall");
    x=x+128;

  }

  



  contactEventManager = new ContactEventManager(gameObjects, gameObjectsDeleteList);


  lightIdle = new Animation(light1->GetSprite(), 6, 11, 0.1f, 3);
}

Game::~Game()
{
}

//Starting things
void Game::Start()
{
  flags += b2Draw::e_shapeBit;
  world->SetDebugDraw(drawPhysics);
  drawPhysics->SetFlags(flags);
  world->SetContactListener(contactEventManager);

  AddGameObject(player1);
  AddGameObject(chest1);
  AddGameObject(light1);
  for(int i=0; i<10; i++)
  {
    AddGameObject(Walls[i]);
  }

  textObj1->SetTextStr("Hello game engine");
  idleAnimation = new Animation(player1->GetSprite(), 0, 5, 0.05f, 5);
  runAnimation = new Animation(player1->GetSprite(), 0, 5, 0.08f, 6);

  /*circle->setRadius(2.f);
  circle->setFillColor(sf::Color::Green);
  circle->setOutlineColor(sf::Color::Green);*/
}

void Game::Initialize()
{
  Start();
  MainLoop();
}

void Game::UpdatePhysics()
{
  world->ClearForces();
  world->Step(deltaTime, 8, 8);
}

//Logic, animations, etc
void Game::Update()
{
  deltaTime = gameClock->getElapsedTime().asSeconds();
  gameClock->restart();

  for(auto &gameObject : *gameObjects)
  {
    gameObject->Update(deltaTime);
  }

  //circle->setPosition(player1->GetSprite()->getPosition());

  lightIdle->Play(deltaTime);

  if(std::abs(InputSystem::Axis().x) > 0 || std::abs(InputSystem::Axis().y) > 0)
  {
    runAnimation->Play(deltaTime);
  }
  else
  {
    idleAnimation->Play(deltaTime);
  }
}

void Game::MainLoop()
{
  while (window->isOpen())
  {
    while(window->pollEvent(*event))
    {
      if(event->type == sf::Event::Closed)
      {
        window->close();
      }
    }

    UpdatePhysics();
    Input();
    Update();
    Render();
  }
  Destroy();
}

void Game::Render()
{
  for(auto& gameobject: *gameObjectsDeleteList)
  {
      gameObjects->erase(std::remove(gameObjects->begin(), gameObjects->end(), gameobject), gameObjects->end());
      delete gameobject;
  }
  gameObjectsDeleteList->clear();

  window->clear(sf::Color::Black);
  Draw();
  window->display();
}

//Drawing sprites or geometry.
void Game::Draw()
{
  //player1->Draw();
  //window->draw(*circle);

  tileGroup->Draw();
  //tile1->Draw();

  for(auto &gameObject : *gameObjects)
  {
    gameObject->Draw();
  }

  window->draw(*textObj1->GetText());
  world->DebugDraw();
}

//Keyboard, joysticks, etc.
void Game::Input()
{
  //player1->Move();
}

void Game::Destroy()
{
  delete window;
  delete event;
}

void Game::AddGameObject(GameObject* gameObject)
{
  gameObjects->push_back(gameObject);
}