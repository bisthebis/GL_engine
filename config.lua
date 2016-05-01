


function init ()
    print("Lua Init called");
    width = 800;
    height = 600;
    camera = getCamera();
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
    end

end



---Table alphabétique SFML (sf::Keyboard::Key::A == 0 etc)
SFML_KEY = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'}
---Table de conversion CameraDirection <-> int
CAMERA_DIR = {UP = 0, DOWN = 1, LEFT = 2, RIGHT = 3, TOP = 4, BOTTOM = 5}
