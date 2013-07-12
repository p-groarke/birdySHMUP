//
//  CGUI.cpp
//  birdyShmup
//
//  Created by Philippe Groarke on 2013-06-23.
//  Copyright (c) 2013 Groarke and co. All rights reserved.
//

#include "CGUI.h"

CGUI CGUI::gUI;

CGUI::CGUI()
{
    healthBarBackground_.x = 10;
    healthBarBackground_.y = 10;
    healthBarBackground_.w = 104;
    healthBarBackground_.h = 14;
    healthBar_.x = 12;
    healthBar_.y = 12;
    healthBar_.w = 100;
    healthBar_.h = 10;

    black = {0, 0, 0, 0};
    white = {255, 255, 255, 0};

    getReadyPlaying = false;
    getReadyTime = 3500;
    getReadyCounter = 3;

}

CGUI::~CGUI()
{}

void CGUI::getReady()
{
    getReadySurface_ = TTF_RenderText_Blended(getReadyFont_, "Get Ready!", white);
    TTF_SetFontStyle(getReadyFont_, TTF_STYLE_BOLD);
    getReadyPlaying = true;
    
}

void CGUI::onLoad()
{


    getReadyFont_ = TTF_OpenFont(Path.font1Path.c_str(), 2);
    pointFont_ = TTF_OpenFont(Path.font1Path.c_str(), 26);

    if (pointFont_ == NULL)
    {
        printf("Unable to load font: %s %s \n", pointFont_, TTF_GetError());
    }

    TTF_SetFontStyle(pointFont_, TTF_STYLE_BOLD);
}

void CGUI::onLoop(CPlayer* player)
{
    // Check player life
    healthBar_.w = player->getLife() / PLAYER_LIFE * 100;

    pointText_ = std::to_string(player->getPlayerPoints());

    points_ = TTF_RenderText_Blended(pointFont_, pointText_.c_str(), white);

}

void CGUI::onRender(SDL_Surface* surfDisplay)
{
    SDL_FillRect(surfDisplay, &healthBarBackground_,
                 SDL_MapRGB(surfDisplay->format, 0, 0, 0));
    SDL_FillRect(surfDisplay, &healthBar_,
                 SDL_MapRGB(surfDisplay->format, 255, 255, 0));


    CSurface::OnDraw(surfDisplay, points_, WWIDTH / 2 - points_->w, 10);

    if (getReadyPlaying)
    {
        getReadyFont_ = TTF_OpenFont(Path.font1Path.c_str(), getReadyCounter);

        getReadySurface_ = TTF_RenderText_Blended(getReadyFont_, "Get Ready!",
                                                  white);
        TTF_SetFontStyle(getReadyFont_, TTF_STYLE_BOLD);

        getReadyCounter += 2;

        if (getReadyCounter >= 64) getReadyCounter = 64;

        CSurface::OnDraw(surfDisplay, getReadySurface_,
                         (WWIDTH / 2) - (getReadySurface_->w / 2),
                         WHEIGHT / 3) - (getReadySurface_->h / 2);

        if (SDL_GetTicks() > getReadyTime) getReadyPlaying = false;
        
    }

}

void CGUI::onCleanup()
{
    TTF_CloseFont(pointFont_);
}