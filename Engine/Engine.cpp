#include "Engine.h"
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_mixer.h>
#include "ErrorHandler.h"

void Engine::resize(int w, int h, Uint32 flags)
{
	m_iWidth = w;
	m_iHeight = h;

	m_pScreen = SDL_SetVideoMode(w,h, bpp, SDL_HWSURFACE | SDL_DOUBLEBUF |flags);

    if( flags & SDL_FULLSCREEN )
        m_bFullScreen = true;
    else
        m_bFullScreen = false;
}

Engine::Engine()
: m_pScreen(NULL)
{
	SDL_Init( SDL_INIT_VIDEO | SDL_INIT_TIMER );
	TTF_Init();

    //Initialize SDL_Mixer
	int audio_rate = 22050;
    Uint16 audio_format = AUDIO_S16SYS; /* 16-bit stereo */
    int audio_channels = 2;
    int audio_buffers = 4096;
    Mix_OpenAudio(audio_rate, audio_format, audio_channels, audio_buffers);

	m_bMinimized = false;
    m_bQuit = false;

	m_iFps = 0;
	last_tick = 0;
	m_iMaxFps = 60;
	tick = 0;

	m_pKeyboard = Keyboard::getInstance();
	m_pMouse = Mouse::getInstance();
}

Engine::~Engine()
{
    Mix_CloseAudio();
	TTF_Quit();
	SDL_Quit();
}

void Engine::init(int width, int height)
{
    set_Icon();
	resize( width, height );
	try
	{
        additional_init();
	}
	catch( GameException e )
	{
        handleException(e);
        m_bQuit = true;
	}
}

void Engine::run()
{
    try
    {
        //Main Loop
        while( m_bQuit == false )
        {
            tick = SDL_GetTicks() - last_tick;
            if(tick < 1000/m_iMaxFps)
                continue;

            handle_framerate();
            handle_events();

            //if( ! m_bMinimized )
            //{
                SDL_FillRect( m_pScreen, &m_pScreen->clip_rect,
                            SDL_MapRGB( m_pScreen->format, 0x00, 0x00, 0x00 ) );
                render( m_pScreen );
                calc( ((float)tick)/1000 );
            //}
            //else
            //    on_minimize();

            SDL_Flip( m_pScreen );
        }
    }
    catch (GameException e)
    {
        handleException(e);
        //m_bQuit = true;
    }
}

void Engine::handle_events()
{
	SDL_Event event;
	while ( SDL_PollEvent( &event ) ) {
		switch(event.type)
		{
		case SDL_KEYDOWN :
			m_pKeyboard->onKeyDown(event.key.keysym.sym, event.key.keysym.mod,
                                    char(event.key.keysym.unicode) );
			break;

		case SDL_KEYUP :
			m_pKeyboard->onKeyUp(event.key.keysym.sym, event.key.keysym.mod,
                                    char(event.key.keysym.unicode) );
			break;

		case SDL_MOUSEMOTION :
			m_pMouse->onMouseMotion(event.motion.x , event.motion.y, event.motion.state,
							event.motion.xrel, event.motion.yrel );
			break;

		case SDL_MOUSEBUTTONDOWN :
			m_pMouse->onMouseDown(event.button.x , event.button.y, event.button.button);
			break;

		case SDL_MOUSEBUTTONUP :
			m_pMouse->onMouseUp(event.button.x , event.button.y, event.button.button);
			break;

		case SDL_ACTIVEEVENT :
			m_bMinimized = !event.active.gain;
			break;

		case SDL_QUIT :
			m_bQuit = true;
			break;

		default :
			break;
		}
	}
}

void Engine::handle_framerate()
{
	static int temp_fps = 0;
	static int total_time = 0;

	total_time += tick;
	if( total_time >= 1000 )
	{
		total_time = 0;
		m_iFps = temp_fps;
		temp_fps = 0;
	}
	else
		temp_fps++;

	last_tick = SDL_GetTicks();
}

void Engine::set_caption(const std::string& c)
{
	m_sCaption = c;
	SDL_WM_SetCaption( m_sCaption.c_str(), 0 );
}

bool Engine::toggleFullScreen()
{
    Uint32 flag = 0;

    if(m_bFullScreen == false)
        flag |= SDL_FULLSCREEN;

    resize( m_iWidth, m_iHeight, flag );

    return true;//SDL_WM_ToggleFullScreen(m_pScreen);
}
