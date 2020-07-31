graphics = require "graphics"
window = require "window"

function engine_load()

end

function engine_update()

end

function engine_draw()
    graphics.rect(20,20,50,50)
end

function engine_error(msg)
    print(msg)
    os.exit()
end