#pragma once

#include "Object.h"
#include "StaticObject.h"
#include "TextureManager.h"
#include <Controller.h>
#include <Player.h>


class Gift : public StaticObject {
public:
    
    Gift();

    void onCollision(Object& other);

};