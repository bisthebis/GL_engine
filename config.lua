


function init ()
    print("Lua Init called");
    cameraDefaultRotationSpeed = 5;
    width = 800;
    height = 600;
    camera = getCamera();
    projectionType = getProjectionType();

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
    end

end



---Table alphabétique SFML (sf::Keyboard::Key::A == 0 etc) AJOUTER UN A L'INDICE
SFML_KEY = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z' }
SFML_KEY[37] = 'esc'
SFML_KEY[68] = '+'; SFML_KEY[69] = '-'; SFML_KEY[70] = '*'; SFML_KEY[71] = '/'
--- Table de conversion CameraDirection <-> int
CAMERA_DIR = {UP = 0, DOWN = 1, LEFT = 2, RIGHT = 3, TOP = 4, BOTTOM = 5}
