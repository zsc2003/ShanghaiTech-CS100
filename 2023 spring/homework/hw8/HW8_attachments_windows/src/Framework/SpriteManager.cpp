#include "SpriteManager.hpp"

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <SOIL/SOIL.h>

#include "utils.hpp"
#include <iostream>

SpriteManager::SpriteManager() : m_spriteInfos() {
	m_spriteInfos.insert({ EncodeAnim(IMGID_BACKGROUND, ANIMID_NO_ANIMATION), SpriteInfo{"background.png", 800, 600, 800, 600} });
	m_spriteInfos.insert({ EncodeAnim(IMGID_SUN, ANIMID_IDLE_ANIM), SpriteInfo{"sun_spritesheet.png", 512, 512, 80, 80, 6, 12} });
	m_spriteInfos.insert({ EncodeAnim(IMGID_SHOVEL, ANIMID_NO_ANIMATION), SpriteInfo{"shovel.png", 80, 80, 80, 80} });
	m_spriteInfos.insert({ EncodeAnim(IMGID_COOLDOWN_MASK, ANIMID_NO_ANIMATION), SpriteInfo{"seedpacket_cooldown.png", 50, 70, 50, 70} });

	m_spriteInfos.insert({ EncodeAnim(IMGID_SEED_SUNFLOWER, ANIMID_NO_ANIMATION), SpriteInfo{"seedpacket_sunflower.png", 50, 70, 50, 70} });
	m_spriteInfos.insert({ EncodeAnim(IMGID_SEED_PEASHOOTER, ANIMID_NO_ANIMATION), SpriteInfo{"seedpacket_peashooter.png", 50, 70, 50, 70} });
	m_spriteInfos.insert({ EncodeAnim(IMGID_SEED_WALLNUT, ANIMID_NO_ANIMATION), SpriteInfo{"seedpacket_wallnut.png", 50, 70, 50, 70} });
	m_spriteInfos.insert({ EncodeAnim(IMGID_SEED_CHERRY_BOMB, ANIMID_NO_ANIMATION), SpriteInfo{"seedpacket_cherry_bomb.png", 50, 70, 50, 70} });
	m_spriteInfos.insert({ EncodeAnim(IMGID_SEED_REPEATER, ANIMID_NO_ANIMATION), SpriteInfo{"seedpacket_repeater.png", 50, 70, 50, 70} });

	m_spriteInfos.insert({ EncodeAnim(IMGID_SUNFLOWER, ANIMID_IDLE_ANIM), SpriteInfo{"sunflower_spritesheet.png", 512, 512, 80, 80, 6, 24} });
	m_spriteInfos.insert({ EncodeAnim(IMGID_PEASHOOTER, ANIMID_IDLE_ANIM), SpriteInfo{"peashooter_spritesheet.png", 512, 512, 80, 80, 6, 24} });
	m_spriteInfos.insert({ EncodeAnim(IMGID_WALLNUT, ANIMID_IDLE_ANIM), SpriteInfo{"wallnut_spritesheet.png", 512, 512, 80, 80, 6, 32} });
	m_spriteInfos.insert({ EncodeAnim(IMGID_CHERRY_BOMB, ANIMID_IDLE_ANIM), SpriteInfo("cherry_bomb_spritesheet.png", 512, 512, 120, 120, 4, 14) });
	m_spriteInfos.insert({ EncodeAnim(IMGID_REPEATER, ANIMID_IDLE_ANIM), SpriteInfo("repeater_spritesheet.png", 512, 512, 80, 80, 6, 24) });
	m_spriteInfos.insert({ EncodeAnim(IMGID_WALLNUT_CRACKED, ANIMID_IDLE_ANIM), SpriteInfo{"wallnut_cracked_spritesheet.png", 512, 512, 80, 80, 6, 32} });

	m_spriteInfos.insert({ EncodeAnim(IMGID_REGULAR_ZOMBIE, ANIMID_WALK_ANIM), SpriteInfo{"zombie_walk_spritesheet.png", 1024, 1024, 100, 139, 10, 46} });
	m_spriteInfos.insert({ EncodeAnim(IMGID_REGULAR_ZOMBIE, ANIMID_EAT_ANIM), SpriteInfo{"zombie_eat_spritesheet.png", 1024, 1024, 100, 139, 10, 39} });
	m_spriteInfos.insert({ EncodeAnim(IMGID_BUCKET_HEAD_ZOMBIE, ANIMID_WALK_ANIM), SpriteInfo{"bucket_head_walk_spritesheet.png", 1024, 1024, 100, 139, 10, 46} });
	m_spriteInfos.insert({ EncodeAnim(IMGID_BUCKET_HEAD_ZOMBIE, ANIMID_EAT_ANIM), SpriteInfo{"bucket_head_eat_spritesheet.png", 1024, 1024, 100, 139, 10, 39} });
	m_spriteInfos.insert({ EncodeAnim(IMGID_POLE_VAULTING_ZOMBIE, ANIMID_WALK_ANIM), SpriteInfo{"pole_vaulter_walk_spritesheet.png", 1024, 1024, 100, 180, 10, 44} });
	m_spriteInfos.insert({ EncodeAnim(IMGID_POLE_VAULTING_ZOMBIE, ANIMID_EAT_ANIM), SpriteInfo{"pole_vaulter_eat_spritesheet.png", 1024, 1024, 100, 180, 10, 27} });
	m_spriteInfos.insert({ EncodeAnim(IMGID_POLE_VAULTING_ZOMBIE, ANIMID_RUN_ANIM), SpriteInfo{"pole_vaulter_run_spritesheet.png", 2048, 2048, 300, 180, 6, 36} });
	m_spriteInfos.insert({ EncodeAnim(IMGID_POLE_VAULTING_ZOMBIE, ANIMID_JUMP_ANIM), SpriteInfo{"pole_vaulter_jump_spritesheet.png", 2048, 2048, 500, 180, 4, 42} });

	m_spriteInfos.insert({ EncodeAnim(IMGID_PEA, ANIMID_NO_ANIMATION), SpriteInfo{"pea.png", 28, 28, 28, 28} });
	m_spriteInfos.insert({ EncodeAnim(IMGID_EXPLOSION, ANIMID_NO_ANIMATION), SpriteInfo{"explosion.png", 240, 227, 240, 227} });

	m_spriteInfos.insert({ EncodeAnim(IMGID_ZOMBIES_WON, ANIMID_NO_ANIMATION), SpriteInfo{"ZombiesWon.jpg", 564, 468, 564, 468} });

	LoadSprites();
}

bool SpriteManager::LoadSprites(){
	glEnable(GL_DEPTH_TEST);
	for (auto& asset : m_spriteInfos) {

		int width, height;
		unsigned char* image = SOIL_load_image(asset.second.filename.c_str(), &width, &height, 0, SOIL_LOAD_RGBA);

		//GLuint texture;
		//glGenTextures(1, &texture);
		//glBindTexture(GL_TEXTURE_2D, texture);
		//glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		////glGenerateMipmaps(GL_TEXTURE_2D);
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
		//gluBuild2DMipmaps(GL_TEXTURE_2D, 3, width, height, GL_RGB, GL_UNSIGNED_BYTE, image);
		//SOIL_free_image_data(image);

		GLuint texture = SOIL_load_OGL_texture(asset.second.filename.c_str(), SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID,
																					 SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_COMPRESS_TO_DXT);
		if (0 == texture) {
			std::cout << "Error loading " << asset.second.filename << std::endl << "-- SOIL loading error : " << SOIL_last_result() << std::endl;
		}

		asset.second.texture = texture;
	}
	return true;
}

//GLuint SpriteManager::GetTexture(ImageID imageID) const {
//	auto it = m_textureMap.find(imageID);
//	if (it == m_textureMap.end()) {
//		return 0;
//	}
//	else {
//		return it->second;
//	}
//}

SpriteInfo SpriteManager::GetSpriteInfo(ImageID imageID, AnimID animID) const {
	auto it = m_spriteInfos.find(EncodeAnim(imageID, animID));
	if (it == m_spriteInfos.end()) {
		return SpriteInfo("", 0, 0, 0, 0);
	}
	else {
		return it->second;
	}
}


