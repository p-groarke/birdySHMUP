//
//  CEnemySpawner.cpp
//  birdyShmup
//
//  Created by Philippe Groarke on 2013-07-08.
//  Copyright (c) 2013 Groarke and co. All rights reserved.
//

#include "CEnemySpawner.h"

CEnemySpawner::CEnemySpawner()
{

}

CEnemySpawner::~CEnemySpawner()
{}

bool CEnemySpawner::onLoad()
{
    FilePaths Path;

    // Todo: Read these values from text file

    for (int i = 0; i < 10; ++i)
    {
        CEnemy* entity1_ = new CEnemy();
        if (entity1_->onLoad(Path.entity1Path.c_str(), 64, 64, 8) == false)
            return false;

        // Init offscreen
        entity1_->setY(-200);

        entity1_->setType(ENTITY_TYPE_ENEMY1);
        CEntity::entityList.push_back(entity1_);
        wave1Enemies_.push_back(entity1_);
    }

    return true;
}

void CEnemySpawner::onLoop()
{
    
}

void CEnemySpawner::onRender()
{
    enemyAnimator();
}

void CEnemySpawner::enemyAnimator()
{
    if (Wave1.startTime >= SDL_GetTicks() || Wave1.animationStarted)
    {
        Wave1.animationStarted = true;
        
        if (!Wave1.animationFinished)
        {
            for (int i = 0; i < wave1Enemies_.size(); ++i)
            {
                Wave1.animationFinished = animStraightLine(wave1Enemies_[i],
                                                           i * 100, 200, 10);
            }
        }
    }
}

bool CEnemySpawner::animStraightLine(CEnemy* enemy, const int x, const int y,
                                     const float speed)
{
    float deltaX = x - enemy->getX();
    float deltaY = y - enemy->getY();

    // Est-ce que nous somme tres proche?
    if (sqrtf(powf(deltaX, 2) + powf(deltaY, 2)) <= speed)
    {
        enemy->setX(x);
        enemy->setY(y);
        return true;
    }

    float teta = asinf(deltaY / sqrtf(powf(deltaX, 2) + powf(deltaY, 2)));

    float newX = cosf(teta) * speed;
    float newY = sinf(teta) * speed;

    if (newY <= 1) newY = speed;

    enemy->setX(enemy->getX() + newX);
    enemy->setY(enemy->getY() + newY);

    return false;
}