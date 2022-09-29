#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <vector>
#include <list>
#include "MoveAtoBObject.h"
#include "Utils.h"
#include "InputMgr.h"
#include "Branch.h"
#include "Player.h"
#include "ResourceMgr.h"

using namespace sf;

void UpdateBranches(vector<Branch*>& branches, int& current, vector<Vector2f>& posArr)
{
    current = (current + 1) % branches.size();

    for (int i = 0; i < branches.size(); ++i)
    {
        int index = (current + i) % branches.size();
        branches[index]->SetPosition(posArr[i]);
        if (i == branches.size() - 1)
        {
            branches[index]->SetSide((Sides)Utils::RandomRange(0, 2));
        }
    }
}

int main()
{

    VideoMode vm(1920, 1080);
    RenderWindow window(vm, "Timber!!", Style::Default);

    auto resourceMgr = ResourceMgr::GetInstance();

    Sound timeOutSound;
    timeOutSound.setBuffer(
        *resourceMgr->GetSoundBuffer("sound/out_of_time.wav"));

    Texture texBackground;
    texBackground.loadFromFile("graphics/background.png");
    Texture texTree;
    texTree.loadFromFile("graphics/tree.png");
    Texture texBee;
    texBee.loadFromFile("graphics/bee.png");
    Texture texCloud;
    texCloud.loadFromFile("graphics/cloud.png");
    Texture texBranch;
    texBranch.loadFromFile("graphics/branch.png");

    Texture texPlayer;
    texPlayer.loadFromFile("graphics/player.png");
    Texture texRIP;
    texRIP.loadFromFile("graphics/rip.png");
    Texture texAxe;
    texAxe.loadFromFile("graphics/axe.png");

    std::list<SpriteGameObject*> gameObjectList;
    gameObjectList.push_back(new SpriteGameObject(texBackground));

    std::vector<float> startVector = { 2000, -300 };
    std::vector<float> endVector = { -300, 2000 };
    for (int i = 0; i < 3; ++i)
    {
        auto movingObj = new MoveAtoBObject(texCloud);
        auto index = Utils::RandomRange(0, 2);
        movingObj->Set(
            { 200, 400 }, { 100, 400 },
            { startVector[index], 0 }, { endVector[index], 0 });
        gameObjectList.push_back(movingObj);
    }

    vector<Branch*> branches(6);
    int currentBranch = -1;

    // 1080 - 10 - 900 = 170


    Vector2u size = window.getSize();
    SpriteGameObject* tree = 
        new SpriteGameObject(texTree, Vector2f(size.x * 0.5f, 910));
    tree->SetOrigin(Origins::BC);
    gameObjectList.push_back(tree);

    for (int i = 0; i < branches.size(); ++i)
    {
        branches[i] = new Branch(texBranch, tree);
        branches[i]->SetSide((Sides)Utils::RandomRange(0, 2));
        gameObjectList.push_back(branches[i]);
    }

    {
        auto movingObj = new MoveAtoBObject(texBee);
        movingObj->Set(
            { 200, 400 }, { 500, 1000 },
            { 2000, 0 }, { -100, 0 });
        gameObjectList.push_back(movingObj);
    }

    Player* player = new Player(texPlayer, texRIP, texAxe);
    gameObjectList.push_back(player);
    player->Set(tree->GetPosition());

    for (auto go : gameObjectList)
    {
         go->Init();
    }

    vector<Vector2f> branchPosArr(branches.size());
    float x = branches[0]->GetPosition().x;
    float y = 800;
    float offset = branches[0]->GetSize().y;
    offset += 100;
    for (int i = 0; i < branches.size(); ++i)
    {
        branchPosArr[i] = Vector2f(x, y);
        y -= offset;
    }
    UpdateBranches(branches, currentBranch, branchPosArr);

    sf::Font font;
    font.loadFromFile("fonts/KOMIKAP_.ttf");

    // UI OBJ CREATES
    sf::Text messageText;
    messageText.setFont(font);
    messageText.setCharacterSize(75);
    messageText.setFillColor(Color::White);
    messageText.setString("Press Enter to start!");
    Utils::SetOrigin(messageText, Origins::MC);

    messageText.setPosition(
        size.x * 0.5f,
        size.y * 0.5f
    );

    Text scoreText;
    scoreText.setFont(font);
    scoreText.setCharacterSize(100);
    scoreText.setFillColor(Color::White);

    scoreText.setPosition(20, 20);

    Vector2f timerBarSize(400, 80);
    RectangleShape timerBar;
    timerBar.setSize(timerBarSize);
    timerBar.setFillColor(Color::Red);
    timerBar.setPosition(size.x * 0.5f - timerBarSize.x * 0.5f, size.y - 100);

    float duration = 4.0f;
    float timer = duration;
    bool isPause = true;
    int score = 0;
    scoreText.setString("Score = " + to_string(score));

    Clock clock;
    while (window.isOpen())
    {
        Time dt = clock.restart();
        InputMgr::ClearInput();
        Event ev;
        while (window.pollEvent(ev))
        {
            InputMgr::UpdateInput(ev);
        }

        if (Keyboard::isKeyPressed(Keyboard::Escape))
        {
            window.close();
            continue;
        }

        if (InputMgr::GetKeyDown(Keyboard::Return))
        {
            if (timer > 0.f)
            {
                isPause = !isPause;
            }
            else
            {
                messageText.setString("Press Enter to start!");
                Utils::SetOrigin(messageText, Origins::MC);
                timer = duration;
                score = 0;
                //
            }
        }

        size = window.getSize();
        float deltaTime = isPause ? 0.f : dt.asSeconds();
        // UI Update
        timer -= deltaTime;
        if (timer < 0.f)
        {
            if (!isPause)
            {
                timeOutSound.play();
            }

            timer = 0.f;
            isPause = true;
            messageText.setString("Time Over!!");
            Utils::SetOrigin(messageText, Origins::MC);
        }

        float normTime = timer / duration;
        float timerSizeX = timerBarSize.x * normTime;
        timerBar.setSize({ timerSizeX, timerBarSize.y });
        timerBar.setPosition(size.x * 0.5f - timerSizeX * 0.5f, size.y - 100);

        // GO Update

        if (InputMgr::GetKeyDown(Keyboard::Key::Space))
        {
            UpdateBranches(branches, currentBranch, branchPosArr);
        }


        for (auto go : gameObjectList)
        {
            go->Update(deltaTime);
        }

        scoreText.setString("SCORE: " + to_string(score));

        // Draw
        window.clear();
        for (auto go : gameObjectList)
        {
            go->Draw(window);
        }

        if (isPause)
        {
            window.draw(messageText);
        }

        window.draw(scoreText);
        window.draw(timerBar);
        window.display();
    }
    
    for (auto go : gameObjectList)
    {
        go->Release();
        delete go;
    }
    gameObjectList.clear();

    return 0;
}