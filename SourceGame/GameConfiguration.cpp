#include "GameConfiguration.h"

/* Khi đặt static member phải khởi tạo như vậy */
map<const char*, double>* GameConfiguration::globalsConfigurationDouble = 0;
map<const char*, const char*>* GameConfiguration::globalsConfigurationString = 0;


/* Lấy 1 thống số ra từ 1 key cho trước */
double GameConfiguration::GetConfiguration(const char * key)
{
	/* Hướng dẫn: Đọc singleton pattern để hiểu cách viết này */
	if (globalsConfigurationDouble == 0)
	{
		globalsConfigurationDouble = new map<const char*, double>();

		/* window_width, window_height là kích thước cửa sổ */
		globalsConfigurationDouble->insert(pair<const char*, double>("window_width", 512));
		globalsConfigurationDouble->insert(pair<const char*, double>("window_height", 448));

		/* backbuffer_width, backbuffer_height là kích thước của backbuffer */
		globalsConfigurationDouble->insert(pair<const char*, double>("backbuffer_width", 222));
		globalsConfigurationDouble->insert(pair<const char*, double>("backbuffer_height", 240));

		/* fps là frame_per_second càng lớn càng mượt nhưng nó sử dụng nhiều cpu hơn */
		globalsConfigurationDouble->insert(pair<const char*, double>("fps", 120));

		/* thời gian đổi frame mặc định của animation là 100 milis, cứ sau 100 milis thì animation sẽ đổi 1 frame */
		globalsConfigurationDouble->insert(pair<const char*, double>("object_animation_time_default", 100));

		/* trọng lực mặc định của đối tượng 80 (px/s^2) */
		globalsConfigurationDouble->insert(pair<const char*, double>("object_default_ay", -2050));


		/*  PLAYER  */
		globalsConfigurationDouble->insert(pair<const char*, double>("player_vx", 190)); /* 60 pixel/s */
		globalsConfigurationDouble->insert(pair<const char*, double>("player_blink_vx", -100)); /* 60 pixel/s */
		globalsConfigurationDouble->insert(pair<const char*, double>("player_vy_jump", 550)); /* 60 pixel/s */
		globalsConfigurationDouble->insert(pair<const char*, double>("player_bulle_delay", 300)); 
		globalsConfigurationDouble->insert(pair<const char*, double>("player_animation_time_default", 25));
		globalsConfigurationDouble->insert(pair<const char*, double>("player_blink_time", 20));
		globalsConfigurationDouble->insert(pair<const char*, double>("player_blink_delay", 2000));
		globalsConfigurationDouble->insert(pair<const char*, double>("player_blink_can't_control_delay", 200));

		globalsConfigurationDouble->insert(pair<const char*, double>("playerbullet_dx", 5)); 

		globalsConfigurationDouble->insert(pair<const char*, double>("worm_vx", 75));
		globalsConfigurationDouble->insert(pair<const char*, double>("worm_dy", 2));
		globalsConfigurationDouble->insert(pair<const char*, double>("worm_y_climp", 16));
		globalsConfigurationDouble->insert(pair<const char*, double>("worm_ay", -250));

		globalsConfigurationDouble->insert(pair<const char*, double>("domes_dx", 1));

		globalsConfigurationDouble->insert(pair<const char*, double>("floater_vx", 80));
		globalsConfigurationDouble->insert(pair<const char*, double>("floater_dy", 2));
		globalsConfigurationDouble->insert(pair<const char*, double>("floater_shoot_time", 1500));
		globalsConfigurationDouble->insert(pair<const char*, double>("floater_shoot_delay", 300));
		globalsConfigurationDouble->insert(pair<const char*, double>("floater_r", 3));
	


		/* TODO tạo thêm các giá trị cấu hình double game tại đây 
		Ví dụ: globalsConfiguration->insert(pair<const char*, double>("gia_tri_key", 10)); 10 la gia tri cua gia_tri_key
		*/

		
	}
	/* trả ra giá trị cấu hình tại key */
	return globalsConfigurationDouble->at(key);
}

const char * GameConfiguration::GetConfigurationString(const char * key)
{
	/* Hướng dẫn: Đọc singleton pattern để hiểu cách viết này */
	if (globalsConfigurationString == 0)
	{
		globalsConfigurationString = new map<const char*, const char*>();

		/* Tiêu đề của cửa sổ */
		globalsConfigurationString->insert(pair<const char*,const char*>("window_title", "Master Blaster"));
		globalsConfigurationString->insert(pair<const char*, const  char*>("window_class", "win_game"));

		/* TODO tạo thêm các giá trị cấu hình string game tại đây
		Ví dụ: globalsConfiguration->insert(pair<const char*, const char*>("gia_tri_key", "value")); "value" la gia tri cua gia_tri_key
		*/

	}
	/* trả ra giá trị cấu hình tại key */
	return globalsConfigurationString->at(key);
}

GameConfiguration::GameConfiguration()
{
}

GameConfiguration::~GameConfiguration()
{
}
