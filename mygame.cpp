#include "mygame.h"

MyGame::MyGame(const std::string& name, const std::string& version) : Game(name, version), m_cubeCount(0)
{
    Config.InitialWidth = 800;
    Config.InitialHeight = 600;
    Config.ClearColor = Vector3f(.22f, .22f, .22f);

#ifdef OSWINDOWS
    ResourceManager<Texture>::SetBasePath("../../media/textures/");
    ResourceManager<Shader>::SetBasePath("../../media/shaders/");
    ResourceManager<Font>::SetBasePath("../../media/fonts/");
    ResourceManager<Model>::SetBasePath("../../media/models/");
    ResourceManager<Sound>::SetBasePath("../../media/sounds/");
#else
    ResourceManager<Texture>::SetBasePath("./media/textures/");
    ResourceManager<Shader>::SetBasePath("./media/shaders/");
    ResourceManager<Font>::SetBasePath("./media/fonts/");
    ResourceManager<Model>::SetBasePath("./media/models/");
    ResourceManager<Sound>::SetBasePath("./media/sounds/");
#endif

}

MyGame::~MyGame()
{
}


bool MyGame::LoadResource()
{
    // Build scene graph
    ContainerNode* root = new ContainerNode();
    OrthographicProjectionNode* ortho = new OrthographicProjectionNode();

    Texture* texTile = Texture::Get("!tile.png");
    Texture* texStair = Texture::Get("!stair.png");
    Font* texFont = Font::Get("!DroidSans.ttf|texture_size=256");


    Cube* floor = new Cube(Vector3f(50.f, 1.f, 50.f), 50.f, "Floor");
    floor->SetTexture(texTile);
    root->AddChild(floor);
    floor->AddToPhysic(0, Vector3f(0, -.5f, 0));


    // Stair
    float sw = 1.f; // stair depth
    float sh = 1.0f; // stair height
    for(int i = 0; i < 5; ++i)
    {
        Cube* stair = new Cube(Vector3f(6.f, sh, sw), 4);
        stair->SetTexture(texStair);
        root->AddChild(stair);
        stair->AddToPhysic(0, Vector3f(0, sh / 2.f + (i * sh), 5 + (i * sw)));
    }

    TextNode* title = new TextNode(texFont, 12.f, "TAK game sample");
    title->SetShader(Shader::Get("!nolight"));
    title->SetPositionAbsolute(10, GetScene().GetParams().GetHeight() - 25, 0);
    ortho->AddChild(title);

    TextNode* instruction = new TextNode(texFont, 12.f, "Drag and hold left mouse button to rotate, hold right mouse button to zoom");
    instruction->SetShader(Shader::Get("!nolight"));
    instruction->SetPositionAbsolute(10, GetScene().GetParams().GetHeight() - 45, 0);
    ortho->AddChild(instruction);

    m_txtFps = new TextNode(texFont);
    m_txtFps->SetShader(Shader::Get("!nolight"));
    m_txtFps->SetPositionAbsolute(10, GetScene().GetParams().GetHeight() - 65, 0);
    ortho->AddChild(m_txtFps);

    m_txtCubeCount = new TextNode(texFont);
    m_txtCubeCount->SetShader(Shader::Get("!nolight"));
    m_txtCubeCount->SetPositionAbsolute(10, GetScene().GetParams().GetHeight() - 85, 0);
    ortho->AddChild(m_txtCubeCount);



    Cube* pc1;

    // front wall
    pc1 = new Cube(Vector3f(5.5f, 7.f, .5f), 10.f);
    pc1->SetTexture(texTile);
    root->AddChild(pc1);
    pc1->AddToPhysic(0, Vector3f(0, pc1->GetSize().y / 2.f, 9.75f));

    // right wall
    pc1 = new Cube(Vector3f(.5f, 7.f, 10.f), 10.f);
    pc1->SetTexture(texTile);
    root->AddChild(pc1);
    pc1->AddToPhysic(0, Vector3f(-3, pc1->GetSize().y / 2.f, 5));

    // right wall
    pc1 = new Cube(Vector3f(.5f, 7.f, 10.f), 10.f);
    pc1->SetTexture(texTile);
    root->AddChild(pc1);
    pc1->AddToPhysic(0, Vector3f(3, pc1->GetSize().y / 2.f, 5));

    // Flag engine logo
    Sprite* flag = new Sprite(128, 128, Texture::Get("!engineflag.png"));
    flag->SetShader(Shader::Get("!nolight"));
    flag->SetPositionAbsolute(GetScene().GetParams().GetWidth() - flag->GetWidth() / 2.f, flag->GetHeight() / 2.f - 20.f, 0);
    ortho->AddChild(flag);

    root->AddChild(ortho);
    GetScene().SetRoot(root);

    // Setup camera:
    Camera* camera = new LookAtCamera(Vector3f(0, 0, 5), 25.f);
    GetScene().SetCamera(camera);

    return true;
}

bool MyGame::UnloadResource()
{
    return true;
}

void MyGame::Update(float elapsedTime)
{
    static float spawnTimer = 0;

    spawnTimer += elapsedTime;

    if(spawnTimer >= 0.15f)
    {
        Cube* c = new Cube(Vector3f(1.f, 1.f, 1.f));
        c->SetTexture(Texture::Get("!debug.png"));
        GetScene().GetRoot()->AddChild(c);
        RigidBody* rb = c->AddToPhysic(1, Vector3f(0, 25, 7.5));
        rb->ApplyForce(Vector3f(0, -10.f, 0));
        spawnTimer = 0;

        m_cubeCount++;
    }

    std::ostringstream fps;
    fps << "FPS: " << GetFps();
    m_txtFps->SetText(fps.str());

    std::ostringstream CubeCount;
    CubeCount << "Cube count: " << m_cubeCount;
    m_txtCubeCount->SetText(CubeCount.str());
}

void MyGame::KeyPressEvent(unsigned char key)
{
    SoundNode* sound01 = new SoundNode(Vector3f(0, 0, 0), Sound::Get("!bip.wav"));
    GetScene().GetRoot()->AddChild(sound01);
}

void MyGame::KeyReleaseEvent(unsigned char key)
{
}

void MyGame::MouseMoveEvent(int x, int y)
{
}

void MyGame::MousePressEvent(const MOUSE_BUTTON &button, int x, int y)
{
    switch(button)
    {
        case MOUSE_BUTTON_MIDDLE:
            GetScene().GetRoot()->ShowGraph(false);
            break;
    }
}

void MyGame::MouseReleaseEvent(const MOUSE_BUTTON &button, int x, int y)
{
}

void MyGame::WindowFocusEvent(bool hasFocus)
{
}

void MyGame::WindowResizeEvent(int width, int height)
{
}

Shader* MyGame::GetDefaultShader()
{
    return Shader::Get("!default");
}

Texture* MyGame::GetDefaultTexture()
{
    return Texture::Get("!default.png|mipmap=false");
}
