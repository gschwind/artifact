
bin_PROGRAMS = code000 code001 code002
code000_SOURCES = code000.cxx config.cxx event_handler.cxx game.cxx gl_utils.cxx render.cxx rstring.cxx rwave.cxx scene.cxx vcontrol.cxx
code000_LDADD = @GL_LIBS@ @IL_LIBS@ @ILU_LIBS@ @ILUT_LIBS@ @SDL_LIBS@
code000_CPPFLAGS = -g @GL_CFLAGS@ @IL_CFLAGS@ @ILU_CFLAGS@ @ILUT_CFLAGS@ @SDL_CFLAGS@

code001_SOURCES = code001.cxx config.cxx palette_window.cxx editor_main.cxx map.cxx gtk_map.cxx gtk_gl.cxx glmap.cxx gl_utils.cxx gl_object.cxx data_file.cxx
code001_CPPFLAGS = -g -lfl @GTKGL_CFLAGS@ @IL_CFLAGS@ @ILU_CFLAGS@ @ILUT_CFLAGS@ @GTK_CFLAGS@ @SDL_CFLAGS@ -DGTK_DISABLE_DEPRECATED=1 -DGDK_DISABLE_DEPRECATED=1 -DGDK_PIXBUF_DISABLE_DEPRECATED=1 -DG_DISABLE_DEPRECATED=1
code001_LDADD = @GTKGL_LIBS@ @GTK_LIBS@ @SDL_LIBS@ @IL_LIBS@ @ILU_LIBS@ @ILUT_LIBS@ 

code002_SOURCES = code002.cxx data_file.cxx data_value.cxx
code002_CPPFLAGS = -g -lfl @GTKGL_CFLAGS@ @IL_CFLAGS@ @ILU_CFLAGS@ @ILUT_CFLAGS@ @GTK_CFLAGS@ @SDL_CFLAGS@ -DGTK_DISABLE_DEPRECATED=1 -DGDK_DISABLE_DEPRECATED=1 -DGDK_PIXBUF_DISABLE_DEPRECATED=1 -DG_DISABLE_DEPRECATED=1
code002_LDADD = @GTKGL_LIBS@ @GTK_LIBS@ @SDL_LIBS@ @IL_LIBS@ @ILU_LIBS@ @ILUT_LIBS@ 
	
