LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE := zip
LOCAL_MODULE_FILENAME := libzip

LOCAL_SRC_FILES := ../lib/mkstemp.c ../lib/zip_add.c ../lib/zip_add_dir.c ../lib/zip_add_entry.c ../lib/zip_buffer.c ../lib/zip_close.c ../lib/zip_delete.c ../lib/zip_dir_add.c ../lib/zip_dirent.c ../lib/zip_discard.c ../lib/zip_entry.c ../lib/zip_err_str.c ../lib/zip_error.c ../lib/zip_error_clear.c ../lib/zip_error_get.c ../lib/zip_error_get_sys_type.c ../lib/zip_error_strerror.c ../lib/zip_error_to_str.c ../lib/zip_extra_field.c ../lib/zip_extra_field_api.c ../lib/zip_fclose.c ../lib/zip_fdopen.c ../lib/zip_file_add.c ../lib/zip_file_error_clear.c ../lib/zip_file_error_get.c ../lib/zip_file_get_comment.c ../lib/zip_file_get_external_attributes.c ../lib/zip_file_get_offset.c ../lib/zip_file_rename.c ../lib/zip_file_replace.c ../lib/zip_file_set_comment.c ../lib/zip_file_set_external_attributes.c ../lib/zip_file_set_mtime.c ../lib/zip_file_strerror.c ../lib/zip_filerange_crc.c ../lib/zip_fopen.c ../lib/zip_fopen_encrypted.c ../lib/zip_fopen_index.c ../lib/zip_fopen_index_encrypted.c ../lib/zip_fread.c ../lib/zip_get_archive_comment.c ../lib/zip_get_archive_flag.c ../lib/zip_get_compression_implementation.c ../lib/zip_get_encryption_implementation.c ../lib/zip_get_file_comment.c ../lib/zip_get_name.c ../lib/zip_get_num_entries.c ../lib/zip_get_num_files.c ../lib/zip_io_util.c ../lib/zip_memdup.c ../lib/zip_name_locate.c ../lib/zip_new.c ../lib/zip_open.c ../lib/zip_rename.c ../lib/zip_replace.c ../lib/zip_set_archive_comment.c ../lib/zip_set_archive_flag.c ../lib/zip_set_default_password.c ../lib/zip_set_file_comment.c ../lib/zip_set_file_compression.c ../lib/zip_set_name.c ../lib/zip_source_begin_write.c ../lib/zip_source_buffer.c ../lib/zip_source_call.c ../lib/zip_source_close.c ../lib/zip_source_commit_write.c ../lib/zip_source_crc.c ../lib/zip_source_deflate.c ../lib/zip_source_error.c ../lib/zip_source_file.c ../lib/zip_source_filep.c ../lib/zip_source_free.c ../lib/zip_source_function.c ../lib/zip_source_is_deleted.c ../lib/zip_source_layered.c ../lib/zip_source_open.c ../lib/zip_source_pkware.c ../lib/zip_source_read.c ../lib/zip_source_remove.c ../lib/zip_source_rollback_write.c ../lib/zip_source_seek.c ../lib/zip_source_seek_write.c ../lib/zip_source_stat.c ../lib/zip_source_supports.c ../lib/zip_source_tell.c ../lib/zip_source_tell_write.c ../lib/zip_source_window.c ../lib/zip_source_write.c ../lib/zip_source_zip.c ../lib/zip_source_zip_new.c ../lib/zip_stat.c ../lib/zip_stat_index.c ../lib/zip_stat_init.c ../lib/zip_strerror.c ../lib/zip_string.c ../lib/zip_unchange.c ../lib/zip_unchange_all.c ../lib/zip_unchange_archive.c ../lib/zip_unchange_data.c ../lib/zip_utf-8.c

ifeq ($(PM5_CONFIG),debug_android_armeabi-v7a)
  LOCAL_C_INCLUDES := $(LOCAL_PATH)/../man $(LOCAL_PATH)/../lib $(LOCAL_PATH)/../regress $(LOCAL_PATH)/. $(LOCAL_PATH)/../examples $(LOCAL_PATH)/../xcode $(LOCAL_PATH)/../src $(LOCAL_PATH)/../m4 $(LOCAL_PATH)/../lib/.deps $(LOCAL_PATH)/../regress/.deps $(LOCAL_PATH)/../examples/.deps $(LOCAL_PATH)/../xcode/libzip.xcodeproj $(LOCAL_PATH)/../xcode/libzip.xcodeproj/project.xcworkspace $(LOCAL_PATH)/../src/.deps
  LOCAL_CFLAGS := -Werror -D_DEBUG -mfloat-abi=softfp -mfpu=neon -ffast-math -fvisibility=hidden -fno-inline-functions -fno-omit-frame-pointer -g
  LOCAL_CPPFLAGS := -Wno-conversion-null -Wno-invalid-offsetof -Wno-deprecated-declarations -fvisibility=hidden -fno-rtti -fno-exceptions -std=c++14
  LOCAL_CONLYFLAGS := -std=c11
  cmd-strip :=
  include $(BUILD_STATIC_LIBRARY)
endif

ifeq ($(PM5_CONFIG),debug_android_x86)
  LOCAL_C_INCLUDES := $(LOCAL_PATH)/../man $(LOCAL_PATH)/../lib $(LOCAL_PATH)/../regress $(LOCAL_PATH)/. $(LOCAL_PATH)/../examples $(LOCAL_PATH)/../xcode $(LOCAL_PATH)/../src $(LOCAL_PATH)/../m4 $(LOCAL_PATH)/../lib/.deps $(LOCAL_PATH)/../regress/.deps $(LOCAL_PATH)/../examples/.deps $(LOCAL_PATH)/../xcode/libzip.xcodeproj $(LOCAL_PATH)/../xcode/libzip.xcodeproj/project.xcworkspace $(LOCAL_PATH)/../src/.deps
  LOCAL_CFLAGS := -Werror -D_DEBUG -ffast-math -fvisibility=hidden -fno-inline-functions -fno-omit-frame-pointer -g
  LOCAL_CPPFLAGS := -Wno-conversion-null -Wno-invalid-offsetof -Wno-deprecated-declarations -fvisibility=hidden -fno-rtti -fno-exceptions -std=c++14
  LOCAL_CONLYFLAGS := -std=c11
  cmd-strip :=
  include $(BUILD_STATIC_LIBRARY)
endif

ifeq ($(PM5_CONFIG),debug_android_arm64-v8a)
  LOCAL_C_INCLUDES := $(LOCAL_PATH)/../man $(LOCAL_PATH)/../lib $(LOCAL_PATH)/../regress $(LOCAL_PATH)/. $(LOCAL_PATH)/../examples $(LOCAL_PATH)/../xcode $(LOCAL_PATH)/../src $(LOCAL_PATH)/../m4 $(LOCAL_PATH)/../lib/.deps $(LOCAL_PATH)/../regress/.deps $(LOCAL_PATH)/../examples/.deps $(LOCAL_PATH)/../xcode/libzip.xcodeproj $(LOCAL_PATH)/../xcode/libzip.xcodeproj/project.xcworkspace $(LOCAL_PATH)/../src/.deps
  LOCAL_CFLAGS := -Werror -D_DEBUG -ffast-math -fvisibility=hidden -fno-inline-functions -fno-omit-frame-pointer -g
  LOCAL_CPPFLAGS := -Wno-conversion-null -Wno-invalid-offsetof -Wno-deprecated-declarations -fvisibility=hidden -fno-rtti -fno-exceptions -std=c++14
  LOCAL_CONLYFLAGS := -std=c11
  cmd-strip :=
  include $(BUILD_STATIC_LIBRARY)
endif

ifeq ($(PM5_CONFIG),debug_android_x86_64)
  LOCAL_C_INCLUDES := $(LOCAL_PATH)/../man $(LOCAL_PATH)/../lib $(LOCAL_PATH)/../regress $(LOCAL_PATH)/. $(LOCAL_PATH)/../examples $(LOCAL_PATH)/../xcode $(LOCAL_PATH)/../src $(LOCAL_PATH)/../m4 $(LOCAL_PATH)/../lib/.deps $(LOCAL_PATH)/../regress/.deps $(LOCAL_PATH)/../examples/.deps $(LOCAL_PATH)/../xcode/libzip.xcodeproj $(LOCAL_PATH)/../xcode/libzip.xcodeproj/project.xcworkspace $(LOCAL_PATH)/../src/.deps
  LOCAL_CFLAGS := -Werror -D_DEBUG -ffast-math -fvisibility=hidden -fno-inline-functions -fno-omit-frame-pointer -g
  LOCAL_CPPFLAGS := -Wno-conversion-null -Wno-invalid-offsetof -Wno-deprecated-declarations -fvisibility=hidden -fno-rtti -fno-exceptions -std=c++14
  LOCAL_CONLYFLAGS := -std=c11
  cmd-strip :=
  include $(BUILD_STATIC_LIBRARY)
endif

ifeq ($(PM5_CONFIG),profile_android_armeabi-v7a)
  LOCAL_C_INCLUDES := $(LOCAL_PATH)/../man $(LOCAL_PATH)/../lib $(LOCAL_PATH)/../regress $(LOCAL_PATH)/. $(LOCAL_PATH)/../examples $(LOCAL_PATH)/../xcode $(LOCAL_PATH)/../src $(LOCAL_PATH)/../m4 $(LOCAL_PATH)/../lib/.deps $(LOCAL_PATH)/../regress/.deps $(LOCAL_PATH)/../examples/.deps $(LOCAL_PATH)/../xcode/libzip.xcodeproj $(LOCAL_PATH)/../xcode/libzip.xcodeproj/project.xcworkspace $(LOCAL_PATH)/../src/.deps
  LOCAL_CFLAGS := -Werror -DNDEBUG -mfloat-abi=softfp -mfpu=neon -ffast-math -fvisibility=hidden -fno-inline-functions -ffunction-sections -fdata-sections -fno-omit-frame-pointer -g -O3
  LOCAL_CPPFLAGS := -Wno-conversion-null -Wno-invalid-offsetof -Wno-deprecated-declarations -fvisibility=hidden -fno-rtti -fno-exceptions -std=c++14
  LOCAL_CONLYFLAGS := -std=c11
  cmd-strip :=
  include $(BUILD_STATIC_LIBRARY)
endif

ifeq ($(PM5_CONFIG),profile_android_x86)
  LOCAL_C_INCLUDES := $(LOCAL_PATH)/../man $(LOCAL_PATH)/../lib $(LOCAL_PATH)/../regress $(LOCAL_PATH)/. $(LOCAL_PATH)/../examples $(LOCAL_PATH)/../xcode $(LOCAL_PATH)/../src $(LOCAL_PATH)/../m4 $(LOCAL_PATH)/../lib/.deps $(LOCAL_PATH)/../regress/.deps $(LOCAL_PATH)/../examples/.deps $(LOCAL_PATH)/../xcode/libzip.xcodeproj $(LOCAL_PATH)/../xcode/libzip.xcodeproj/project.xcworkspace $(LOCAL_PATH)/../src/.deps
  LOCAL_CFLAGS := -Werror -DNDEBUG -ffast-math -fvisibility=hidden -fno-inline-functions -ffunction-sections -fdata-sections -fno-omit-frame-pointer -g -O3
  LOCAL_CPPFLAGS := -Wno-conversion-null -Wno-invalid-offsetof -Wno-deprecated-declarations -fvisibility=hidden -fno-rtti -fno-exceptions -std=c++14
  LOCAL_CONLYFLAGS := -std=c11
  cmd-strip :=
  include $(BUILD_STATIC_LIBRARY)
endif

ifeq ($(PM5_CONFIG),profile_android_arm64-v8a)
  LOCAL_C_INCLUDES := $(LOCAL_PATH)/../man $(LOCAL_PATH)/../lib $(LOCAL_PATH)/../regress $(LOCAL_PATH)/. $(LOCAL_PATH)/../examples $(LOCAL_PATH)/../xcode $(LOCAL_PATH)/../src $(LOCAL_PATH)/../m4 $(LOCAL_PATH)/../lib/.deps $(LOCAL_PATH)/../regress/.deps $(LOCAL_PATH)/../examples/.deps $(LOCAL_PATH)/../xcode/libzip.xcodeproj $(LOCAL_PATH)/../xcode/libzip.xcodeproj/project.xcworkspace $(LOCAL_PATH)/../src/.deps
  LOCAL_CFLAGS := -Werror -DNDEBUG -ffast-math -fvisibility=hidden -fno-inline-functions -ffunction-sections -fdata-sections -fno-omit-frame-pointer -g -O3
  LOCAL_CPPFLAGS := -Wno-conversion-null -Wno-invalid-offsetof -Wno-deprecated-declarations -fvisibility=hidden -fno-rtti -fno-exceptions -std=c++14
  LOCAL_CONLYFLAGS := -std=c11
  cmd-strip :=
  include $(BUILD_STATIC_LIBRARY)
endif

ifeq ($(PM5_CONFIG),profile_android_x86_64)
  LOCAL_C_INCLUDES := $(LOCAL_PATH)/../man $(LOCAL_PATH)/../lib $(LOCAL_PATH)/../regress $(LOCAL_PATH)/. $(LOCAL_PATH)/../examples $(LOCAL_PATH)/../xcode $(LOCAL_PATH)/../src $(LOCAL_PATH)/../m4 $(LOCAL_PATH)/../lib/.deps $(LOCAL_PATH)/../regress/.deps $(LOCAL_PATH)/../examples/.deps $(LOCAL_PATH)/../xcode/libzip.xcodeproj $(LOCAL_PATH)/../xcode/libzip.xcodeproj/project.xcworkspace $(LOCAL_PATH)/../src/.deps
  LOCAL_CFLAGS := -Werror -DNDEBUG -ffast-math -fvisibility=hidden -fno-inline-functions -ffunction-sections -fdata-sections -fno-omit-frame-pointer -g -O3
  LOCAL_CPPFLAGS := -Wno-conversion-null -Wno-invalid-offsetof -Wno-deprecated-declarations -fvisibility=hidden -fno-rtti -fno-exceptions -std=c++14
  LOCAL_CONLYFLAGS := -std=c11
  cmd-strip :=
  include $(BUILD_STATIC_LIBRARY)
endif

ifeq ($(PM5_CONFIG),profile_enableasserts_android_armeabi-v7a)
  LOCAL_C_INCLUDES := $(LOCAL_PATH)/../man $(LOCAL_PATH)/../lib $(LOCAL_PATH)/../regress $(LOCAL_PATH)/. $(LOCAL_PATH)/../examples $(LOCAL_PATH)/../xcode $(LOCAL_PATH)/../src $(LOCAL_PATH)/../m4 $(LOCAL_PATH)/../lib/.deps $(LOCAL_PATH)/../regress/.deps $(LOCAL_PATH)/../examples/.deps $(LOCAL_PATH)/../xcode/libzip.xcodeproj $(LOCAL_PATH)/../xcode/libzip.xcodeproj/project.xcworkspace $(LOCAL_PATH)/../src/.deps
  LOCAL_CFLAGS := -Werror -DNDEBUG -DAK_ENABLE_ASSERTS -mfloat-abi=softfp -mfpu=neon -ffast-math -fvisibility=hidden -fno-inline-functions -ffunction-sections -fdata-sections -fno-omit-frame-pointer -g -O3
  LOCAL_CPPFLAGS := -Wno-conversion-null -Wno-invalid-offsetof -Wno-deprecated-declarations -fvisibility=hidden -fno-rtti -fno-exceptions -std=c++14
  LOCAL_CONLYFLAGS := -std=c11
  cmd-strip :=
  include $(BUILD_STATIC_LIBRARY)
endif

ifeq ($(PM5_CONFIG),profile_enableasserts_android_x86)
  LOCAL_C_INCLUDES := $(LOCAL_PATH)/../man $(LOCAL_PATH)/../lib $(LOCAL_PATH)/../regress $(LOCAL_PATH)/. $(LOCAL_PATH)/../examples $(LOCAL_PATH)/../xcode $(LOCAL_PATH)/../src $(LOCAL_PATH)/../m4 $(LOCAL_PATH)/../lib/.deps $(LOCAL_PATH)/../regress/.deps $(LOCAL_PATH)/../examples/.deps $(LOCAL_PATH)/../xcode/libzip.xcodeproj $(LOCAL_PATH)/../xcode/libzip.xcodeproj/project.xcworkspace $(LOCAL_PATH)/../src/.deps
  LOCAL_CFLAGS := -Werror -DNDEBUG -DAK_ENABLE_ASSERTS -ffast-math -fvisibility=hidden -fno-inline-functions -ffunction-sections -fdata-sections -fno-omit-frame-pointer -g -O3
  LOCAL_CPPFLAGS := -Wno-conversion-null -Wno-invalid-offsetof -Wno-deprecated-declarations -fvisibility=hidden -fno-rtti -fno-exceptions -std=c++14
  LOCAL_CONLYFLAGS := -std=c11
  cmd-strip :=
  include $(BUILD_STATIC_LIBRARY)
endif

ifeq ($(PM5_CONFIG),profile_enableasserts_android_arm64-v8a)
  LOCAL_C_INCLUDES := $(LOCAL_PATH)/../man $(LOCAL_PATH)/../lib $(LOCAL_PATH)/../regress $(LOCAL_PATH)/. $(LOCAL_PATH)/../examples $(LOCAL_PATH)/../xcode $(LOCAL_PATH)/../src $(LOCAL_PATH)/../m4 $(LOCAL_PATH)/../lib/.deps $(LOCAL_PATH)/../regress/.deps $(LOCAL_PATH)/../examples/.deps $(LOCAL_PATH)/../xcode/libzip.xcodeproj $(LOCAL_PATH)/../xcode/libzip.xcodeproj/project.xcworkspace $(LOCAL_PATH)/../src/.deps
  LOCAL_CFLAGS := -Werror -DNDEBUG -DAK_ENABLE_ASSERTS -ffast-math -fvisibility=hidden -fno-inline-functions -ffunction-sections -fdata-sections -fno-omit-frame-pointer -g -O3
  LOCAL_CPPFLAGS := -Wno-conversion-null -Wno-invalid-offsetof -Wno-deprecated-declarations -fvisibility=hidden -fno-rtti -fno-exceptions -std=c++14
  LOCAL_CONLYFLAGS := -std=c11
  cmd-strip :=
  include $(BUILD_STATIC_LIBRARY)
endif

ifeq ($(PM5_CONFIG),profile_enableasserts_android_x86_64)
  LOCAL_C_INCLUDES := $(LOCAL_PATH)/../man $(LOCAL_PATH)/../lib $(LOCAL_PATH)/../regress $(LOCAL_PATH)/. $(LOCAL_PATH)/../examples $(LOCAL_PATH)/../xcode $(LOCAL_PATH)/../src $(LOCAL_PATH)/../m4 $(LOCAL_PATH)/../lib/.deps $(LOCAL_PATH)/../regress/.deps $(LOCAL_PATH)/../examples/.deps $(LOCAL_PATH)/../xcode/libzip.xcodeproj $(LOCAL_PATH)/../xcode/libzip.xcodeproj/project.xcworkspace $(LOCAL_PATH)/../src/.deps
  LOCAL_CFLAGS := -Werror -DNDEBUG -DAK_ENABLE_ASSERTS -ffast-math -fvisibility=hidden -fno-inline-functions -ffunction-sections -fdata-sections -fno-omit-frame-pointer -g -O3
  LOCAL_CPPFLAGS := -Wno-conversion-null -Wno-invalid-offsetof -Wno-deprecated-declarations -fvisibility=hidden -fno-rtti -fno-exceptions -std=c++14
  LOCAL_CONLYFLAGS := -std=c11
  cmd-strip :=
  include $(BUILD_STATIC_LIBRARY)
endif

ifeq ($(PM5_CONFIG),release_android_armeabi-v7a)
  LOCAL_C_INCLUDES := $(LOCAL_PATH)/../man $(LOCAL_PATH)/../lib $(LOCAL_PATH)/../regress $(LOCAL_PATH)/. $(LOCAL_PATH)/../examples $(LOCAL_PATH)/../xcode $(LOCAL_PATH)/../src $(LOCAL_PATH)/../m4 $(LOCAL_PATH)/../lib/.deps $(LOCAL_PATH)/../regress/.deps $(LOCAL_PATH)/../examples/.deps $(LOCAL_PATH)/../xcode/libzip.xcodeproj $(LOCAL_PATH)/../xcode/libzip.xcodeproj/project.xcworkspace $(LOCAL_PATH)/../src/.deps
  LOCAL_CFLAGS := -Werror -DNDEBUG -DAK_OPTIMIZED -mfloat-abi=softfp -mfpu=neon -ffast-math -fvisibility=hidden -fno-inline-functions -ffunction-sections -fdata-sections -O3
  LOCAL_CPPFLAGS := -Wno-conversion-null -Wno-invalid-offsetof -Wno-deprecated-declarations -fvisibility=hidden -fno-rtti -fno-exceptions -std=c++14
  LOCAL_CONLYFLAGS := -std=c11
  include $(BUILD_STATIC_LIBRARY)
endif

ifeq ($(PM5_CONFIG),release_android_x86)
  LOCAL_C_INCLUDES := $(LOCAL_PATH)/../man $(LOCAL_PATH)/../lib $(LOCAL_PATH)/../regress $(LOCAL_PATH)/. $(LOCAL_PATH)/../examples $(LOCAL_PATH)/../xcode $(LOCAL_PATH)/../src $(LOCAL_PATH)/../m4 $(LOCAL_PATH)/../lib/.deps $(LOCAL_PATH)/../regress/.deps $(LOCAL_PATH)/../examples/.deps $(LOCAL_PATH)/../xcode/libzip.xcodeproj $(LOCAL_PATH)/../xcode/libzip.xcodeproj/project.xcworkspace $(LOCAL_PATH)/../src/.deps
  LOCAL_CFLAGS := -Werror -DNDEBUG -DAK_OPTIMIZED -ffast-math -fvisibility=hidden -fno-inline-functions -ffunction-sections -fdata-sections -O3
  LOCAL_CPPFLAGS := -Wno-conversion-null -Wno-invalid-offsetof -Wno-deprecated-declarations -fvisibility=hidden -fno-rtti -fno-exceptions -std=c++14
  LOCAL_CONLYFLAGS := -std=c11
  include $(BUILD_STATIC_LIBRARY)
endif

ifeq ($(PM5_CONFIG),release_android_arm64-v8a)
  LOCAL_C_INCLUDES := $(LOCAL_PATH)/../man $(LOCAL_PATH)/../lib $(LOCAL_PATH)/../regress $(LOCAL_PATH)/. $(LOCAL_PATH)/../examples $(LOCAL_PATH)/../xcode $(LOCAL_PATH)/../src $(LOCAL_PATH)/../m4 $(LOCAL_PATH)/../lib/.deps $(LOCAL_PATH)/../regress/.deps $(LOCAL_PATH)/../examples/.deps $(LOCAL_PATH)/../xcode/libzip.xcodeproj $(LOCAL_PATH)/../xcode/libzip.xcodeproj/project.xcworkspace $(LOCAL_PATH)/../src/.deps
  LOCAL_CFLAGS := -Werror -DNDEBUG -DAK_OPTIMIZED -ffast-math -fvisibility=hidden -fno-inline-functions -ffunction-sections -fdata-sections -O3
  LOCAL_CPPFLAGS := -Wno-conversion-null -Wno-invalid-offsetof -Wno-deprecated-declarations -fvisibility=hidden -fno-rtti -fno-exceptions -std=c++14
  LOCAL_CONLYFLAGS := -std=c11
  include $(BUILD_STATIC_LIBRARY)
endif

ifeq ($(PM5_CONFIG),release_android_x86_64)
  LOCAL_C_INCLUDES := $(LOCAL_PATH)/../man $(LOCAL_PATH)/../lib $(LOCAL_PATH)/../regress $(LOCAL_PATH)/. $(LOCAL_PATH)/../examples $(LOCAL_PATH)/../xcode $(LOCAL_PATH)/../src $(LOCAL_PATH)/../m4 $(LOCAL_PATH)/../lib/.deps $(LOCAL_PATH)/../regress/.deps $(LOCAL_PATH)/../examples/.deps $(LOCAL_PATH)/../xcode/libzip.xcodeproj $(LOCAL_PATH)/../xcode/libzip.xcodeproj/project.xcworkspace $(LOCAL_PATH)/../src/.deps
  LOCAL_CFLAGS := -Werror -DNDEBUG -DAK_OPTIMIZED -ffast-math -fvisibility=hidden -fno-inline-functions -ffunction-sections -fdata-sections -O3
  LOCAL_CPPFLAGS := -Wno-conversion-null -Wno-invalid-offsetof -Wno-deprecated-declarations -fvisibility=hidden -fno-rtti -fno-exceptions -std=c++14
  LOCAL_CONLYFLAGS := -std=c11
  include $(BUILD_STATIC_LIBRARY)
endif


all: $(LOCAL_INSTALLED)