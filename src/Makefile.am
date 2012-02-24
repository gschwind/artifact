bin_PROGRAMS = code000 code001 code002 code003

code000_SOURCES = code000.cxx config.cxx event_handler.cxx game.cxx gl_utils.cxx render.cxx rstring.cxx rwave.cxx scene.cxx vcontrol.cxx
code000_CPPFLAGS = -g @GL_CFLAGS@ @IL_CFLAGS@ @ILU_CFLAGS@ @ILUT_CFLAGS@ @SDL_CFLAGS@ @FT_CFLAGS@@FT_LIBS@
code000_LDADD = @GL_LIBS@ @IL_LIBS@ @ILU_LIBS@ @ILUT_LIBS@ @SDL_LIBS@ @FT_LIBS@

code001_SOURCES = code001.cxx config.cxx palette_window.cxx editor_main.cxx map.cxx gtk_map.cxx gtk_gl.cxx glmap.cxx gl_utils.cxx gl_object.cxx data_file.cxx
code001_CPPFLAGS = -g -lfl @GTKGL_CFLAGS@ @IL_CFLAGS@ @ILU_CFLAGS@ @ILUT_CFLAGS@ @GTK_CFLAGS@ @SDL_CFLAGS@ 
code001_LDADD = @GTKGL_LIBS@ @GTK_LIBS@ @SDL_LIBS@ @IL_LIBS@ @ILU_LIBS@ @ILUT_LIBS@ @FT_LIBS@

code002_SOURCES = code002.cxx data_file.cxx data_value.cxx
code002_CPPFLAGS = -g -lfl @GTKGL_CFLAGS@ @IL_CFLAGS@ @ILU_CFLAGS@ @ILUT_CFLAGS@ @GTK_CFLAGS@ @SDL_CFLAGS@ @FT_CFLAGS@
code002_LDADD = @GTKGL_LIBS@ @GTK_LIBS@ @SDL_LIBS@ @IL_LIBS@ @ILU_LIBS@ @ILUT_LIBS@ @FT_LIBS@

code003_SOURCES = code003.cxx global.cxx gl_shoot_anim_bullet1.cxx gl_cast_bar.cxx ui_player_status.cxx ui_target_status.cxx gl_shoot_anim.cxx ui_toolbar.cxx gl_ship.cxx gl_utils.cxx
code003_CPPFLAGS = -g -lfl @GTKGL_CFLAGS@ @IL_CFLAGS@ @ILU_CFLAGS@ @ILUT_CFLAGS@ @GTK_CFLAGS@ @SDL_CFLAGS@ @FT_CFLAGS@
code003_LDADD = @GTKGL_LIBS@ @GTK_LIBS@ @SDL_LIBS@ @IL_LIBS@ @ILU_LIBS@ @ILUT_LIBS@ @FT_LIBS@
