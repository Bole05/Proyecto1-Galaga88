// Game.cpp
#include "Game.h"
#include "raylib.h"
#include <cstdlib>
#include <ctime>
#include <resource_dir.h> 
#include <algorithm>
#include <random>
#include<vector>
#include "raymath.h"  
#include "Explosion.h"
Game::Game()
    : gameState(MENU)
    , menuTexture{}
    , backgroundTexture{}
    , bossBackgroundTexture{}
    , playerTexture{}
    , bossTexture{}
    , PlyBulletText{}
    , score(0)
    , bestScore(0)
    , bossActive(false)
    , backgroundOffset(0.0f)
    , backgroundSpeed(2.0f)
    , bgTransitionActive(false)
    , bgAlpha(0.0f)
    , bgFadeSpeed(0.05f)
    , bossBgOffset(0.0f)
    , bossBgSpeed(1.5f)
    , formationOffsetX(0.0f)
    , formationDir(1.0f)
    , formationSpeed(60.0f)
{
    playerBullets.resize(MAX_BULLETS);
    enemyBullets.resize(MAX_ENEMY_BULLETS);
    bossBullets.resize(MAX_BOSS_BULLETS);
    playerExplosions.reserve(4);

}


Game::~Game() {
    //texturas
    UnloadTexture(menuTexture);
    UnloadTexture(backgroundTexture);
    UnloadTexture(playerTexture);

    for (Texture2D& t : enemyTextures) UnloadTexture(t);
    enemyTextures.clear();

    UnloadTexture(bossTexture);
    UnloadTexture(PlyBulletText);
    UnloadTexture(explPlayerTex);
    UnloadTexture(explBossTex);
    UnloadTexture(enemyBulletTex);

    //audios
    UnloadSound(sfxPlayerShot);    
    UnloadSound(sfxEnemyHit);
    UnloadSound(sfxPlayerHurt);
   

    UnloadMusicStream(bgmStage);
    UnloadMusicStream(bgmMenu);
    UnloadMusicStream(bgmGameOver);
    CloseAudioDevice();
    CloseWindow();
}

void Game::Init() {
   
    SearchAndSetResourceDir("resources");

    srand((unsigned int)time(nullptr));

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Galaga 88 - Raylib");
    InitAudioDevice();
    SetTargetFPS(90);

   
    {
        // Menú
        Image menuImg = LoadImage("menu inicial.jpg");
        ImageResize(&menuImg, SCREEN_WIDTH, SCREEN_HEIGHT);
        menuTexture = LoadTextureFromImage(menuImg);
        UnloadImage(menuImg);

        // Fondo
        Image bgImg = LoadImage("fonda galaga fabricas.png");
        ImageResize(&bgImg, SCREEN_WIDTH, SCREEN_HEIGHT);
        backgroundTexture = LoadTextureFromImage(bgImg);
        UnloadImage(bgImg);

        Image bossBgImg = LoadImage("NIVELL_BOSS_1.png");
        TraceLog(LOG_INFO, "cargando fondo Boss  w=%d  h=%d", bossBgImg.width, bossBgImg.height);
        ImageResize(&bossBgImg, SCREEN_WIDTH, SCREEN_HEIGHT);
        bossBackgroundTexture = LoadTextureFromImage(bossBgImg);
        TraceLog(LOG_INFO, "ID textura Boss = %u", bossBackgroundTexture.id);
        UnloadImage(bossBgImg);

        // bala enemigo
        Image eBulletImg = LoadImage("gun-bullets-enemy2.png");   // tu sprite
        ImageResize(&eBulletImg, 25, 25);                   // tamaño final
        enemyBulletTex = LoadTextureFromImage(eBulletImg);
        UnloadImage(eBulletImg);                            // ya no la necesitas

        for (auto& b : enemyBullets)   // la misma textura para todas
            b.SetTexture(enemyBulletTex);

        /* ---------- Parámetros del fundido ---------- */
        bgTransitionActive = false;
        bgAlpha = 0.0f;   // opacidad inicial
        bgFadeSpeed = 0.05f;
        bossBgOffset = 0.0f;
        bossBgSpeed = 1.5f;

        // Player
        Image playerImg = LoadImage("99809.png");
        // Por si quieres redimensionar a 40x40
        ImageResize(&playerImg, 75, 75);
        playerTexture = LoadTextureFromImage(playerImg);
        UnloadImage(playerImg);

         //Boss
         Image bossImg = LoadImage("Arcade_-_Galaga_Arrangement_-_King_Galaspark-removebg-preview.png");
         ImageResize(&bossImg, 100, 100);
         bossTexture = LoadTextureFromImage(bossImg);
         UnloadImage(bossImg);
         boss.SetTexture(bossTexture);

         //bullet Player
    
         Image pBulletImg = LoadImage("Galaga88_Sprite_Ampliado-removebg-preview.png");
         ImageResize(&pBulletImg, 46, 40);              // tamaño final de la bala
         Texture2D playerBulletTex = LoadTextureFromImage(pBulletImg);
         UnloadImage(pBulletImg);

         // la misma textura para todas las balas del jugador
         for (auto& b : playerBullets)  
             b.SetTexture(playerBulletTex);


         explPlayerTex = LoadTexture("explosion.png");
         explBossTex = LoadTexture("explosion boss2.png");
           
         //Audios
         sfxPlayerShot = LoadSound("laser3.ogg");
         SetSoundVolume(sfxPlayerShot, 2.5f);

         sfxEnemyHit = LoadSound("hit2.ogg");   
         SetSoundVolume(sfxEnemyHit, 2.0f);

         sfxPlayerHurt = LoadSound("hurt1.ogg");   
         SetSoundVolume(sfxPlayerHurt, 2.0f);

         bgmStage = LoadMusicStream("11. Scroll Stage Music.mp3");
         SetMusicVolume(bgmStage, 1.8f);      // 180 % volumen
         PlayMusicStream(bgmStage);
         
         bgmMenu = LoadMusicStream("02. Game Start.mp3"); 
         SetMusicVolume(bgmMenu, 0.6f);
         PlayMusicStream(bgmMenu);

         bgmGameOver = LoadMusicStream("13. Game Over Music.mp3");   // NUEVO
         SetMusicVolume(bgmGameOver, 0.7f);

         enemyTextures.clear();
         enemyTextures.reserve(NUM_ENEMY_TYPES);

         const char* enemyFiles[NUM_ENEMY_TYPES] =
         {
             "2342_x4-removebg-preview4.png",   // enemy_0  azul-verde
             "34315_x4-removebg-preview3.png",  // enemy_1  amarillo
             "enemy_1_processed1.png",          // enemy_2  rojo-azul
             "enemy_2_processed1.png",          // enemy_3  violeta-azul
                                  
         };

         for (int i = 0; i < NUM_ENEMY_TYPES; ++i)
         {
             Texture2D tex = LoadTexture(enemyFiles[i]);

             if (tex.id == 0)   // aviso si falta el archivo
                 TraceLog(LOG_WARNING, "No se encontró %s", enemyFiles[i]);

             enemyTextures.push_back(tex);
         }
    }

    player.Init();
    boss.Init();
    InitEnemies();
}

void Game::InitEnemies()
{
    constexpr int COLS = 10;
    constexpr int ROWS = 3;
    bool used[ROWS][COLS] = {};          // todo a false

    enemies.clear();
    enemies.resize(MAX_ENEMIES);

    for (auto& e : enemies)
    {
        e.Init();                        // estado, velocities…

        /* elegir celda libre --------------------------------*/
        int col, row;
        do {
            col = GetRandomValue(0, COLS - 1);
            row = GetRandomValue(0, ROWS - 1);
        } while (used[row][col]);

        used[row][col] = true;

        /* coordenadas base de formación ---------------------*/
        float x0 = 40.0f + col * 60.0f;  // separación 60 px
        float y0 = 80.0f + row * 60.0f;

        Rectangle r = e.GetRect();
        r.x = x0;
        r.y = y0;
        e.SetRect(r);                    // (usa tu setter o toca directo)

        /* sprite aleatorio ----------------------------------*/
        int type = GetRandomValue(0, NUM_ENEMY_TYPES - 1);
        e.SetSprite(enemyTextures[type]);   // 2 frames
    }
}

void Game::Update() {

    UpdateMusicStream(bgmStage);
    UpdateMusicStream(bgmMenu);
    UpdateMusicStream(bgmGameOver);
    bool inMenu = (gameState == MENU);
    bool inGame = (gameState == LEVEL1 || gameState == LEVEL2 || gameState == BOSS);
    bool inGameOver = (gameState == GAMEOVER || gameState == WIN);
    if (inMenu) {
        ResumeMusicStream(bgmMenu);
        PauseMusicStream(bgmStage);
        PauseMusicStream(bgmGameOver);
    }
    else if (inGame) {
        ResumeMusicStream(bgmStage);
        PauseMusicStream(bgmMenu);
        PauseMusicStream(bgmGameOver);
    }
    else if (inGameOver) {
        // ??? Lanzar Game-Over solo una vez ???????????????????????
        if (!IsMusicStreamPlaying(bgmGameOver))
            PlayMusicStream(bgmGameOver);   // ? ¡aquí está la clave!

        PauseMusicStream(bgmMenu);
        PauseMusicStream(bgmStage);
    }
  


    float delta = GetFrameTime();
    if (WindowShouldClose()) {
        gameState = GAMEOVER;
    }
    backgroundOffset += backgroundSpeed;
    if (backgroundOffset >= backgroundTexture.height) {
        backgroundOffset = 0.0f;
    }


    switch (gameState) {
    case MENU:
        if (IsKeyPressed(KEY_ENTER)) {
            wave = 1;
            gameState = LEVEL1;
            score = 0;
            player.Init();
            boss.Init();
            InitEnemies();
        }
        break;

    case LEVEL1:
    case LEVEL2:
        formationOffsetX += formationDir * formationSpeed * GetFrameTime();
        if (formationOffsetX < -40.0f || formationOffsetX > 40.0f)  // rebote
            formationDir *= -1.0f;
        player.Update();

        // Player dispara
        if (IsKeyPressed(KEY_SPACE))
        {
            for (auto& pb : playerBullets)
            {
                if (!pb.IsActive())
                {
                    Rectangle pr = player.GetRect();                // ? caja nave
                    Vector2 pos{
                        pr.x + pr.width * 0.5f,   // centro horizontal
                        pr.y                       // borde superior de la nave
                    };

                    pb.Activate(pos);              // bala centrada
                    PlaySound(sfxPlayerShot);
                    break;
                }
            }
        }
        

        // Actualizar balas player
        for (auto& pb : playerBullets) {
            pb.Update();
        }
       

        // Enemigos
        UpdateEnemies();
        EnemyAttack();
        for (auto& eb : enemyBullets) eb.Update();

        /*------------- COMPROBAR LÍMITES Y COLISIÓN ----------------------*/
        for (auto& eb : enemyBullets)
        {
            if (!eb.IsActive()) continue;

            Rectangle r = eb.GetRect();          // rectángulo actualizado

            /* 1) fuera de pantalla ? desactivar */
            if (r.y > SCREEN_HEIGHT) {
                eb.Deactivate();
                continue;
            }

            /* 2) colisión con el jugador */
            if (CheckCollisionRecs(r, player.GetRect()))
            {
                eb.Deactivate();
                player.TakeDamage();
                PlaySound(sfxPlayerHurt);

                /* --- explosión del jugador --- */
                Rectangle pr = player.GetRect();
                Vector2 center{
                    pr.x + pr.width * 0.5f,
                    pr.y + pr.height * (0.5f + 0.20f)
                };
                Explosion ex;
                /*ex.Start(center, explBossTex, 4, 0.10f, 1.4f);
                bossExplosions.push_back(ex);*/
                ex.Start(center, explPlayerTex, 4, 0.08f, 0.55f);
                playerExplosions.push_back(ex);
                /* ------------------------------ */

                if (player.GetLives() <= 0)
                    gameState = GAMEOVER;
            }
        }

        // Si matamos a todos -> Boss
        CheckAllEnemiesDefeated();
        if (gameState == BOSS) {
            bossActive = true;
            boss.Init();
            boss.Activate(true);
        }
        break;
    
case BOSS:
{
    player.Update();
    boss.Update();

    /* ---- DISPARO DEL JUGADOR ------------------------------------ */
    if (IsKeyPressed(KEY_SPACE))
    {
        for (auto& pb : playerBullets)
            if (!pb.IsActive())
            {
                Rectangle pr = player.GetRect();
                Vector2 pos{ pr.x + pr.width * 0.5f, pr.y };
                pb.Activate(pos);
                PlaySound(sfxPlayerShot);
                break;
            }
    }

    /* ---- BALAS DEL JUGADOR -------------------------------------- */
    for (auto& pb : playerBullets)
    {
        pb.Update();

        if (pb.IsActive() && boss.IsActive() &&
            CheckCollisionRecs(pb.GetRect(), boss.GetRect()))
        {
            pb.Deactivate();
            boss.TakeDamage(1);
            score += 50;

            if (boss.GetLife() <= 0 && boss.IsActive())
            {
                boss.Activate(false);            // lo ocultamos
                Rectangle br = boss.GetRect();
                Vector2  c{ br.x + br.width * 0.5f, br.y + br.height * 0.5f };

                Explosion ex;
                //ex.Start(c, explBossTex, 4, 0.10f, 0.5f); // 4 columnas
                //bossExplosions.push_back(ex);
                ex.Start(c,          // posición
                    explBossTex,// textura de la explosión
                    4,          // ? columnas que usa tu sprite-sheet
                    0.10f,      // tiempo por fotograma
                    0.5f);     // escala
                bossExplosions.push_back(ex);
            }
        }
    }

    /* ---- ATAQUE DEL BOSS ---------------------------------------- */
    BossAttack();

    /* ---- BALAS DEL BOSS ----------------------------------------- */
    for (auto& bb : bossBullets) bb.Update();

    for (auto& bb : bossBullets)
    {
        if (!bb.IsActive()) continue;

        if (bb.GetRect().y > SCREEN_HEIGHT) { bb.Deactivate(); continue; }
        if (CheckCollisionRecs(bb.GetRect(), player.GetRect()))
        {
            bb.Deactivate();
            player.TakeDamage();
            PlaySound(sfxPlayerHurt);

            Rectangle pr = player.GetRect();
            Vector2 center{ pr.x + pr.width * 0.5f,
                            pr.y + pr.height * (0.5f + 0.20f) };

            Explosion ex;
            ex.Start(center, explPlayerTex, 4, 0.08f, 0.55f);
            playerExplosions.push_back(ex);

            if (player.GetLives() <= 0) gameState = GAMEOVER;
        }
    }
}
break;
    case GAMEOVER:
    case WIN:
        // Esperar ENTER para volver a MENU
        if (IsKeyPressed(KEY_ENTER)) {
            wave = 1;
            gameState = MENU;
            for (auto& pb : playerBullets) pb.Deactivate();
            for (auto& eb : enemyBullets)  eb.Deactivate();
            for (auto& bb : bossBullets)   bb.Deactivate();
        }
        break;
    }

    if (bgTransitionActive) {
        bgAlpha += bgFadeSpeed;
        if (bgAlpha >= 1.0f) {      // cuando llega a opacidad total…
            bgAlpha = 1.0f;
            bgTransitionActive = false;
        }
        /* ?? scroll del fondo-Boss ????????????????????????????? */
        if (gameState == BOSS || bgTransitionActive)
        {
            bossBgOffset += bossBgSpeed;
            if (bossBgOffset >= bossBackgroundTexture.height)
                bossBgOffset = 0.0f;
        }

        /* ?? guardar récord cuando termina la partida ????????? */
        if ((gameState == GAMEOVER || gameState == WIN) && score > bestScore)
            bestScore = score;
    }
    if (bgTransitionActive) {
        bgAlpha += bgFadeSpeed;              // sube opacidad
        if (bgAlpha >= 0.80f) {              // llega al 80 % máx
            bgAlpha = 0.80f;                 // (ajusta si quieres 1.0f)
            bgTransitionActive = false;      // fundido terminado
        }
    }

    /*????????????????  SCROLL DEL FONDO-BOSS  ???????????*/
    if (gameState == BOSS || bgTransitionActive) {
        bossBgOffset += bossBgSpeed;                         // mueve
        if (bossBgOffset >= bossBackgroundTexture.height)    // reinicia
            bossBgOffset = 0.0f;
    }

    for (auto& ex : playerExplosions) ex.Update();
    playerExplosions.erase(
        std::remove_if(playerExplosions.begin(), playerExplosions.end(),
            [](const Explosion& e) { return !e.IsActive(); }),
        playerExplosions.end());

    for (auto& ex : bossExplosions) ex.Update();
    bossExplosions.erase(
        std::remove_if(bossExplosions.begin(), bossExplosions.end(),
            [](const Explosion& e) { return !e.IsActive(); }),
        bossExplosions.end());
    for (const auto& ex : bossExplosions) ex.Draw();

    /*  Cuando terminen las explosiones del Boss gana el jugador */
    if (bossExplosions.empty() && !boss.IsActive() && gameState == BOSS)
        gameState = WIN;

    /* --------- récord de puntuación --------- */
    if ((gameState == GAMEOVER || gameState == WIN) && score > bestScore)
        bestScore = score;
    }

void Game::Draw()
{
    BeginDrawing();
    ClearBackground(BLACK);

    /*???????????????? 1) FONDO NORMAL con scroll (solo si procede) ?????????????*/
    bool mostrarFondoNormal = (gameState != BOSS) || bgTransitionActive;

    if (mostrarFondoNormal) {
        int yScroll = (int)backgroundOffset % backgroundTexture.height;
        DrawTexture(backgroundTexture, 0, yScroll, WHITE);
        DrawTexture(backgroundTexture, 0,
            yScroll - backgroundTexture.height, WHITE);
    }

    /*???????????????? 2) FONDO-BOSS con scroll propio + alfa ???????????????????*/
    if (gameState == BOSS || bgTransitionActive) {
        Color tint = WHITE;
        tint.a = (unsigned char)(bgAlpha * 255);   // 0–255
        int by = (int)bossBgOffset;
        DrawTexture(bossBackgroundTexture, 0, by, tint);
        DrawTexture(bossBackgroundTexture, 0,
            by - bossBackgroundTexture.height, tint);
    }

    /*???????????????? 3) GAMEPLAY / HUD según estado ???????????????????????????*/
    switch (gameState)
    {
    case MENU:
        if (menuTexture.id) DrawTexture(menuTexture, 0, 0, WHITE);
        DrawText("GALAGA 88", SCREEN_WIDTH / 2 - 100, SCREEN_HEIGHT / 2 - 50, 40, WHITE);
        DrawText("Press ENTER to start", SCREEN_WIDTH / 2 - 130, SCREEN_HEIGHT / 2, 20, WHITE);
        DrawText(TextFormat("Nivel: %d", wave),
            SCREEN_WIDTH / 2 - 60, 40, 32, WHITE);
        break;

    case LEVEL1:
    case LEVEL2:
    case BOSS:
    {
        Rectangle pr = player.GetRect();
        DrawTexture(playerTexture, (int)pr.x, (int)pr.y, WHITE);
        for (auto& e : enemies)                    // 2) recorre la lista
            if (e.IsActive())
                e.Draw(pr);


        if (bossActive && boss.IsActive()) {
            boss.Draw();
            DrawText(TextFormat("Boss HP: %d", boss.GetLife()),
                SCREEN_WIDTH / 2 - 50, 10, 20, RED);
        }

        for (auto& pb : playerBullets) pb.Draw();
        for (auto& eb : enemyBullets)  eb.Draw();
        for (auto& bb : bossBullets)   bb.Draw();

        DrawText(TextFormat("Score: %d", score), 10, 10, 20, WHITE);
        DrawText(TextFormat("Best:  %d", bestScore), 10, 35, 20, YELLOW);
        DrawText(TextFormat("Lives: %d", player.GetLives()),
            SCREEN_WIDTH - 110, 10, 20, WHITE);
        if (wave > 0){ const char* lvlTxt = TextFormat("Nivel: %d", wave);
        int txtW = MeasureText(lvlTxt, 20);      // 20 px de alto ? pequeño
        DrawText(lvlTxt,
            (SCREEN_WIDTH - txtW) / 2,        // centrado en X
            60,                             // Y = 60 px
            20, WHITE);
        }
       
        break;
    }

    case GAMEOVER:
        DrawText("GAME OVER", SCREEN_WIDTH / 2 - 100, SCREEN_HEIGHT / 2 - 50, 40, WHITE);
        DrawText("Press ENTER to return to MENU", SCREEN_WIDTH / 2 - 150, SCREEN_HEIGHT / 2, 20, WHITE);
        break;

    case WIN:
        DrawText("YOU WIN!", SCREEN_WIDTH / 2 - 80, SCREEN_HEIGHT / 2 - 50, 40, GREEN);
        DrawText("Press ENTER to return to MENU", SCREEN_WIDTH / 2 - 150, SCREEN_HEIGHT / 2, 20, WHITE);
        break;
    }
    for (const auto& ex : playerExplosions) ex.Draw();
    for (const auto& ex : bossExplosions)   ex.Draw();
    EndDrawing();
}
void Game::LaunchOrbitRing() {
    constexpr int kRingSize = 5;       // 1 centro + 4 órbitas
    constexpr int kOrbits = kRingSize - 1;

    std::vector<Enemy*> pool;
    for (auto& e : enemies)
        if (e.IsActive() && e.GetState() == EnemyState::FORMATION)
            pool.push_back(&e);
    if (pool.size() < kRingSize) return;

    std::mt19937 rng(static_cast<uint32_t>(GetRandomValue(0, 10000)));
    std::shuffle(pool.begin(), pool.end(), rng);

    Enemy* anchor = pool[0];                 // el del centro
    Rectangle ar = anchor->GetRect();
    Vector2 center{ ar.x + ar.width / 2.0f, ar.y + ar.height / 2.0f };

    const float radius = 80.0f;
    const float speed = 2.5f;
    for (int i = 0; i < kOrbits; ++i) {
        float phase = i * 2 * PI / kOrbits;  // espaciado uniforme
        pool[i + 1]->StartOrbit(anchor, radius, phase, speed);
    }

    for (auto& e : enemies) {
        if (!e.IsActive()) continue;
        if (e.GetState() != EnemyState::FORMATION) continue;
        if (&e == anchor) continue;  // ancla queda quieta

        // 25 % de probabilidad de dive inmediato
        if (GetRandomValue(0, 3) == 0) {
            e.StartDive();
        }
    }
}



void Game::UpdateEnemies() {
    bool lanzarDive = (GetRandomValue(0, 1000) < 2);
    if (GetRandomValue(0, 1000) < 2) LaunchOrbitRing();   // probabilidad 0,2 %

    int iniciados = 0;
    for (auto& e : enemies) {
        if (!e.IsActive()) continue;
        e.SetGroupOffset(formationOffsetX);
        if (e.GetState() == EnemyState::FORMATION) {
            if (lanzarDive && iniciados < 4) {
                e.StartDive();
                iniciados++;
            }
        }
        e.Update();
        Rectangle er2 = e.GetRect();
        bool fueraPantalla =
            er2.x + er2.width  < -20 ||   // se fue por la izq.
            er2.x              > SCREEN_WIDTH + 20 ||   // por la der.
            er2.y > SCREEN_HEIGHT + 20;     // por abajo

        if (fueraPantalla)
        {
            e.Deactivate();
            continue;                // pasamos al siguiente enemigo
        }

        for (auto& pb : playerBullets)
        {
            if (pb.IsActive() && CheckCollisionRecs(pb.GetSweptRect(), e.GetHitBox()))
            {
                pb.Deactivate();
                e.Deactivate();
                score += 10;
                break;                      // sal del bucle de balas
            }
        }
    }
}

void Game::CheckAllEnemiesDefeated() {
    bool allDead = true;
    for (auto& e : enemies)
        if (e.IsActive()) { allDead = false; break; }

    if (!allDead) return;

    /* ---------- Todas las naves destruidas ---------- */
    if (wave == 1)                 // pasamos a la 2.ª oleada
    {
        wave = 2;
        gameState = LEVEL2;
        for (auto& pb : playerBullets) pb.Deactivate();
        for (auto& eb : enemyBullets)  eb.Deactivate();
        for (auto& bb : bossBullets)   bb.Deactivate();

        playerExplosions.clear();
        bossExplosions.clear();
        InitEnemies();             // misma formación / misma dificultad
    }
    else                           // wave == 2  ?  Boss
    {
        wave = 0;
        for (auto& pb : playerBullets) pb.Deactivate();   // balas del jugador
        for (auto& eb : enemyBullets)  eb.Deactivate();   // balas de enemigos
        for (auto& bb : bossBullets)   bb.Deactivate();   // (por si acaso hubiera)
        playerExplosions.clear();                         // quita explosiones
        bossExplosions.clear();
        gameState = BOSS;
        bossActive = true;
        bgTransitionActive = true;
        bgAlpha = 0.0f;

        boss.Init();
        boss.Activate(true);
    }
}

void Game::EnemyAttack() {
    Rectangle pr = player.GetRect();
    Vector2 playerCenter{ pr.x + pr.width * 0.5f,
                          pr.y + pr.height * 0.5f };

    for (auto& e : enemies)
    {
        if (!e.IsActive()) continue;

        Rectangle er = e.GetRect();               // ? posición actual

        // ????????? VISIBILIDAD ??????????
        bool onScreen =
            er.x + er.width > 0 && er.x < SCREEN_WIDTH &&
            er.y + er.height > 0 && er.y < SCREEN_HEIGHT;
        if (!onScreen) continue;                  // … si no se ve, no dispara
        // ?????????????????????????????????

        if (GetRandomValue(0, 100) < 2)           // 2 % de probabilidad
        {
            for (auto& eb : enemyBullets)
            {
                if (!eb.IsActive())
                {
                    Vector2 enemyCenter{ er.x + er.width * 0.5f,
                                         er.y + er.height * 0.5f };

                    Vector2 dir = Vector2Normalize(
                        Vector2Subtract(playerCenter, enemyCenter));
                    Vector2 vel = Vector2Scale(dir, ENEMY_BULLET_SPEED);

                    eb.Activate(enemyCenter, vel);
                    break;
                }
            }
        }
    }
}

void Game::BossAttack()
{
    if (!boss.IsActive()) return;

    /* 5 % de probabilidad cada frame ? lanza 3 balas rectas hacia abajo */
    if (GetRandomValue(0, 100) < 5)
    {
        int lanzadas = 0;
        for (auto& bb : bossBullets)
        {
            if (!bb.IsActive())
            {
                Rectangle br = boss.GetRect();
                Vector2 pos{ br.x + br.width * 0.5f,  br.y + br.height };

                Vector2 vel{ 0,  BOSS_BULLET_SPEED };   // ? recto
                bb.Activate(pos, vel);                  // activa bala

                if (++lanzadas == 3) break;             // solo 3 balas
            }
        }
    }
}