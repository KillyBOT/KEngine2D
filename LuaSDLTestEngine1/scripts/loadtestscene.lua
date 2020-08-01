require "globals"

allEntities = {
    testSprite = {
        transformComponent = 0
        graphicsComponent = 1
    }
}

allComponents = {
    testTransformComponent = {
        componentType = transformComponentID,
        id = 0,
        x = 50,
        y = 50
    }
    testGraphicsComponent = {
        id = graphicsComponentID,
        path = "assets/test.png",
        imgWidth = 50,
        imgHeight = 50
    }
}