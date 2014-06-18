AUX_SOURCE_DIRECTORY(./Camera src_camera)
SOURCE_GROUP("Camera" FILES ${src_camera})
AUX_SOURCE_DIRECTORY(./Core src_core)
SOURCE_GROUP("Core" FILES ${src_core})
AUX_SOURCE_DIRECTORY(./Entity src_entity)
SOURCE_GROUP(Entity FILES ${src_entity})
AUX_SOURCE_DIRECTORY(./Light src_light)
SOURCE_GROUP(Light FILES ${src_light})
AUX_SOURCE_DIRECTORY(./Physical src_physical)
SOURCE_GROUP(Physical FILES ${src_physical})
AUX_SOURCE_DIRECTORY(./Physical/BSDF src_bsdf)
SOURCE_GROUP(Physical/BSDF FILES ${src_bsdf})
AUX_SOURCE_DIRECTORY(./Sampler src_sampler)
SOURCE_GROUP(Sampler FILES ${src_sampler})
AUX_SOURCE_DIRECTORY(./Texture src_texture)
SOURCE_GROUP(Texture FILES ${src_texture})
AUX_SOURCE_DIRECTORY(./Util src_util)
SOURCE_GROUP(Util FILES ${src_util})

ADD_LIBRARY(libsharpray STATIC 
	${src_camera}
	${src_core}
	${src_entity}
	${src_light}
	${src_physical}
	${src_sampler}
	${src_texture}
	${src_util}
	${src_bsdf})