/*===========================================
*   Copyright (C) 2014 All rights reserved.
*   
*   company      : xiaomi
*   author       : root
*   email        : root@xiaomi.com
*   date         ：2014-12-13 11:11:10
*   description  ：
*
=============================================*/
#ifndef _EXT_EXAMPLE_H_
#define _EXT_EXAMPLE_H_

#include <string>
#include "hphp/runtime/base/base-includes.h"
#include "hphp/runtime/ext/extension.h"
#include "yaf_exception.h"


namespace HPHP {

#define DEFAULT_SLASH_CHAR '/'
#define DEFAULT_SLASH_STR "/"

#define IS_SLASH(c) ((c) == '/' || (c) == '\\') 

#define IS_ABSOLUTE_PATH(x) \
    ((x).length() && IS_SLASH((x)[0]))

        
extern Object createObject(const String& obj_typename, Array args);

class YafExtension : public Extension {
public:
    YafExtension():Extension("yaf"){}
    virtual void moduleInit();
    void moduleLoad(Hdf config);
    void moduleLoad(const IniSetting::Map& ini, Hdf config);

private:
    void _loadYafConf(Hdf conf);
    void _initYafActionClass();
    void _initYafControllerClass();
    //初始化request相关class
    void _initYafRequestClass();
    void _initYafRequestHttpClass();
    void _initYafRequestSimpleClass();
    //初始化response相关class

    void _initYafResponseClass();
    void _initYafResponseHttpClass();
    void _initYafResponseClientClass();

    void _initYafApplicationClass();
    void _initYafDispatcherClass();

    void _initYafViewClass();
    void _initYafViewInterfaceClass();
    void _initYafViewSimpleClass();

    void _initYafConfigClass();
    void _initYafConfigSimpleClass();
    void _initYafConfigIniClass();
}; 

class YafRequestData: public RequestEventHandler {

public: 
    std::string ext; 
    std::string base_uri;
    std::string environ;
    std::string directory;
    std::string local_library;
    std::string local_namespaces;
    std::string global_library;
    std::string view_directory;
    std::string view_ext;
    std::string default_module;
    std::string default_controller;
    std::string default_action;
    std::string bootstrap;
    std::string name_separator;
    long        name_separator_len;
    bool   lowcase_path;
    bool   use_spl_autoload;
    bool   throw_exception;
    bool   cache_config;
    bool   action_prefer;
    bool   name_suffix;
    bool   autoload_started;
    bool   running;
    bool   in_exception;
    bool   catch_exception;
    bool   suppressing_warning;
    /* {{{ This only effects internally */
    bool   st_compatible;
    /* }}} */
    long        forward_limit;
    Array       *configs;
    Variant     *modules;
    Variant     *default_route;
/*#if ((PHP_MAJOR_VERSION == 5) && (PHP_MINOR_VERSION < 4))
    uint        buf_nesting;
    void        *buffer;
    void        *owrite_handler;
#endif
*/
    Variant     *active_ini_file_section;
    Variant     *ini_wanted_section;
    int         parsing_flag;
#ifdef YAF_HAVE_NAMESPACE
    bool        use_namespace;
#endif

public:
        virtual void requestInit() {
            this->running          = 0;
            this->in_exception     = 0;
            this->throw_exception  = 1;
            this->catch_exception  = 0;
            //this->directory        = NULL;
            //this->bootstrap        = NULL;
            //this->local_library    = NULL;
            //this->local_namespaces = NULL;
            this->modules          = NULL;
            //this->base_uri         = NULL;
            //this->view_directory   = NULL;
/*
#if ((PHP_MAJOR_VERSION == 5) && (PHP_MINOR_VERSION < 4))
            this->buffer           = NULL;
            this->owrite_handler   = NULL;
            this->buf_nesting      = 0;
#endif
*/
        }

        virtual void requestShutdown() {
        }
        virtual ~YafRequestData(){}
};

DECLARE_EXTERN_REQUEST_LOCAL(YafRequestData, g_yaf_local_data);

}


#endif //_EXT_EXAMPLE_H

