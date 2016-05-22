


function init ()
    print("Lua Init called");
    cameraDefaultRotationSpeed = 5;
    width = 800;
    height = 600;
    camera = getCamera();
    projectionType = getProjectionType();


    LightPos_x = 0.0;
    LightPos_y = 0.0;
    LightPos_z = 3.0;

    escapeCallback = function ()
      print("Leaving via Esc callback");
      quit();
    end

    
end



function handleKey(key)
    if SFML_KEY[key+1] == 'z' then
        pushCamera(camera, CAMERA_DIR.UP)
    elseif SFML_KEY[key+1] == 's' then
        pushCamera(camera, CAMERA_DIR.DOWN)
    elseif SFML_KEY[key+1] == 'q' then
        pushCamera(camera, CAMERA_DIR.LEFT)
    elseif SFML_KEY[key+1] == 'd' then
        pushCamera(camera, CAMERA_DIR.RIGHT)
    elseif SFML_KEY[key+1] == 'a' then
        rotateCamera(camera, -cameraDefaultRotationSpeed, 0)
    elseif SFML_KEY[key+1] == 'e' then
        rotateCamera(camera, cameraDefaultRotationSpeed, 0)
    elseif SFML_KEY[key+1] == 'x' then
        rotateCamera(camera, 0, cameraDefaultRotationSpeed)
    elseif SFML_KEY[key+1] == 'c' then
        rotateCamera(camera, 0, -cameraDefaultRotationSpeed)
    elseif SFML_KEY[key+1] == 'p' then
        switchProjectionType(projectionType)
    elseif SFML_KEY[key+1] == '+' then
        cameraDefaultRotationSpeed = cameraDefaultRotationSpeed + 1
    elseif SFML_KEY[key+1] == '-' then
        cameraDefaultRotationSpeed = cameraDefaultRotationSpeed - 1
    elseif SFML_KEY[key+1] == 'esc' then
        escapeCallback()
--Light
    elseif SFML_KEY[key+1] == '*' then
        LightPos_z = LightPos_z + 1
    elseif SFML_KEY[key+1] == '/' then
        LightPos_z = LightPos_z - 1
    elseif SFML_KEY[key+1] == 'left' then
        LightPos_y = LightPos_y - 1
    elseif SFML_KEY[key+1] == 'right' then
        LightPos_y = LightPos_y + 1
    elseif SFML_KEY[key+1] == 'up' then
        LightPos_x = LightPos_x - 1
    elseif SFML_KEY[key+1] == 'down' then
        LightPos_x = LightPos_x + 1

    end

end



---Table alphabétique SFML (sf::Keyboard::Key::A == 0 etc) AJOUTER UN A L'INDICE
SFML_KEY = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z' }
SFML_KEY[37] = 'esc'
SFML_KEY[68] = '+'; SFML_KEY[69] = '-'; SFML_KEY[70] = '*'; SFML_KEY[71] = '/'
SFML_KEY[72] = 'left'
SFML_KEY[73] = 'right'
SFML_KEY[74] = 'up'
SFML_KEY[75] = 'down'
--- Table de conversion CameraDirection <-> int
CAMERA_DIR = {UP = 0, DOWN = 1, LEFT = 2, RIGHT = 3, TOP = 4, BOTTOM = 5}
