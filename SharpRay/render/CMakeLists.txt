AUX_SOURCE_DIRECTORY(./Camera src_camera)
AUX_SOURCE_DIRECTORY(./Core src_core)
AUX_SOURCE_DIRECTORY(./Entity src_entity)
AUX_SOURCE_DIRECTORY(./Light src_light)
AUX_SOURCE_DIRECTORY(./Physical src_physical)
AUX_SOURCE_DIRECTORY(./Physical/BSDF src_bsdf)
AUX_SOURCE_DIRECTORY(./Sampler src_sampler)
AUX_SOURCE_DIRECTORY(./Texture src_texture)
AUX_SOURCE_DIRECTORY(./Util src_util)

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