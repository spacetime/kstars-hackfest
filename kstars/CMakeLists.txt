add_subdirectory( data )
add_subdirectory( icons )
add_subdirectory( htmesh )
add_subdirectory( tools/whatsinteresting/qml)

Find_package(ZLIB REQUIRED)

if (CFITSIO_FOUND)
  set (fits_SRCS
    fitsviewer/fitshistogram.cpp
    fitsviewer/fitsimage.cpp
    fitsviewer/fitsview.cpp
    fitsviewer/fitsviewer.cpp
    fitsviewer/fitshistogramdraw.cpp
    fitsviewer/fitstab.cpp
)
  set (fitsui_SRCS
    fitsviewer/fitsheaderdialog.ui
    fitsviewer/statform.ui
    indi/streamform.ui
    fitsviewer/fitshistogramui.ui
)
  include_directories(${CFITSIO_INCLUDE_DIR})
endif(CFITSIO_FOUND)

if (INDI_FOUND)
  set (indi_SRCS
    indi/drivermanager.cpp
    indi/servermanager.cpp
    indi/clientmanager.cpp
    indi/guimanager.cpp
    indi/driverinfo.cpp
    indi/deviceinfo.cpp
    indi/indidevice.cpp
    indi/indigroup.cpp
    indi/indiproperty.cpp
    indi/indielement.cpp
    indi/indistd.cpp
    indi/indilistener.cpp
    indi/inditelescope.cpp
    indi/indiccd.cpp
    indi/indifocuser.cpp
    indi/indifilter.cpp
    indi/opsindi.cpp
    indi/telescopewizardprocess.cpp
    indi/streamwg.cpp
    )
  set(indiui_SRCS
    indi/devmanager.ui
    indi/drivermanager.ui
    indi/opsindi.ui
    indi/indihostconf.ui
    indi/streamform.ui
    indi/telescopewizard.ui
    )

if (CFITSIO_FOUND)
   set(ekosui_SRCS
      ekos/opsekos.ui
      ekos/ekosmanager.ui
      ekos/capture.ui
      ekos/focus.ui
      ekos/guide.ui
      ekos/guide/guider.ui
      ekos/guide/rcalibration.ui
   )

   set(ekos_SRCS
      ekos/ekosmanager.cpp
      ekos/capture.cpp
      ekos/focus.cpp
      ekos/guide.cpp
      ekos/opsekos.cpp
      ekos/QProgressIndicator.cpp
      ekos/guide/common.cpp
      ekos/guide/gmath.cpp
      ekos/guide/guider.cpp
      ekos/guide/matr.cpp
      ekos/guide/rcalibration.cpp
      ekos/guide/scroll_graph.cpp
      ekos/guide/vect.cpp
   )
endif(CFITSIO_FOUND)

  include_directories(${INDI_INCLUDE_DIR})
endif(INDI_FOUND)

if (WCSLIB_FOUND)
  include_directories( ${WCSLIB_INCLUDE_DIR} )
endif (WCSLIB_FOUND)

if ( XPLANET_FOUND )
  set (xplanet_SRCS
    xplanet/opsxplanet.cpp
    )
  set(xplanetui_SRCS
    xplanet/opsxplanet.ui
    )
endif ( XPLANET_FOUND )

if ( OPENGL_FOUND )
  include_directories( ${OPENGL_INCLUDE_DIRS} )
  set(kstars_gl_SRCS
    skyglpainter.cpp skymapgldraw.cpp
    )
  add_definitions(-DHAVE_OPENGL)
endif( OPENGL_FOUND )

include_directories(
    ${kstars_SOURCE_DIR}/kstars/tools
    ${kstars_SOURCE_DIR}/kstars/skyobjects
    ${kstars_SOURCE_DIR}/kstars/skycomponents
#    ${CMAKE_SOURCE_DIR}/kstars/kstars/htmesh
#	${CMAKE_SOURCE_DIR}/libkdeedu/extdate
	${ZLIB_INCLUDE_DIR}
	${EIGEN2_INCLUDE_DIR}
)

########### next target ###############
set(libkstarstools_SRCS
	tools/altvstime.cpp
	tools/astrocalc.cpp
	tools/avtplotwidget.cpp
	tools/calendarwidget.cpp
	tools/conjunctions.cpp
	tools/eqplotwidget.cpp
	tools/jmoontool.cpp
	tools/ksconjunct.cpp
	tools/modcalcangdist.cpp
	tools/modcalcapcoord.cpp
	tools/modcalcaltaz.cpp
	tools/modcalcdaylength.cpp
	tools/modcalceclipticcoords.cpp
	tools/modcalcvizequinox.cpp
	tools/modcalcgalcoord.cpp
	tools/modcalcgeodcoord.cpp
	tools/modcalcjd.cpp
	tools/modcalcplanets.cpp
	tools/modcalcsidtime.cpp
	tools/modcalcvlsr.cpp
	tools/observinglist.cpp
	tools/sessionsortfilterproxymodel.cpp
	tools/obslistwizard.cpp
	tools/planetviewer.cpp
	tools/pvplotwidget.cpp
	tools/scriptargwidgets.cpp
	tools/scriptbuilder.cpp
	tools/scriptfunction.cpp
	tools/skycalendar.cpp
	tools/wutdialog.cpp
	tools/whatsinteresting/skyobjlistmodel.cpp
	tools/whatsinteresting/wiview.cpp
	tools/whatsinteresting/modelmanager.cpp
	tools/whatsinteresting/skyobjitem.cpp
	tools/whatsinteresting/wilpsettings.cpp
	tools/whatsinteresting/wiequipsettings.cpp
	tools/whatsinteresting/obsconditions.cpp
	tools/flagmanager.cpp
	tools/moonphasetool.cpp
	tools/starhopper.cpp
	)

kde4_add_ui_files(libkstarstools_SRCS
	tools/altvstime.ui
	tools/argchangeviewoption.ui
	tools/argexportimage.ui
	tools/argloadcolorscheme.ui
	tools/arglooktoward.ui
	tools/argfindobject.ui
	tools/argprintimage.ui
	tools/argsetactionindi.ui
	tools/argsetaltaz.ui
	tools/argsetccdtempindi.ui
	tools/argsetcolor.ui
	tools/argsetdeviceindi.ui
	tools/argsetfilternumindi.ui
	tools/argsetfocusspeedindi.ui
	tools/argsetfocustimeoutindi.ui
	tools/argsetframetypeindi.ui
	tools/argsetgeolocation.ui
	tools/argsetgeolocationindi.ui
	tools/argsetlocaltime.ui
	tools/argsetportindi.ui
	tools/argsetradec.ui
	tools/argsetscopeactionindi.ui
	tools/argsettargetcoordindi.ui
	tools/argsettargetnameindi.ui
	tools/argsettrack.ui
	tools/argsetutcindi.ui
	tools/argshutdownindi.ui
	tools/argstartexposureindi.ui
	tools/argstartfocusindi.ui
	tools/argstartindi.ui
	tools/argswitchindi.ui
	tools/argtimescale.ui
	tools/argwaitfor.ui
	tools/argwaitforkey.ui
	tools/argzoom.ui
	tools/conjunctions.ui
	tools/modcalcangdist.ui
	tools/modcalcapcoord.ui
	tools/modcalcaltaz.ui
	tools/modcalcdaylength.ui
	tools/modcalceclipticcoords.ui
	tools/modcalcvizequinox.ui
	tools/modcalcgalcoord.ui
	tools/modcalcgeod.ui
	tools/modcalcjd.ui
	tools/modcalcplanets.ui
	tools/modcalcsidtime.ui
	tools/modcalcvlsr.ui
	tools/observinglist.ui
	tools/obslistwizard.ui
	tools/optionstreeview.ui
	tools/planetviewer.ui
	tools/scriptbuilder.ui
	tools/scriptnamedialog.ui
	tools/skycalendar.ui
	tools/wutdialog.ui
	tools/flagmanager.ui
	tools/whatsinteresting/wilpsettings.ui
	tools/whatsinteresting/wiequipsettings.ui
        )


set(libkstarscomponents_SRCS
   skycomponents/skylabeler.cpp
   skycomponents/highpmstarlist.cpp
   skycomponents/skymapcomposite.cpp
   skycomponents/skymesh.cpp
   skycomponents/linelistindex.cpp
   skycomponents/linelistlabel.cpp
   skycomponents/noprecessindex.cpp
   skycomponents/listcomponent.cpp
   skycomponents/pointlistcomponent.cpp
   skycomponents/solarsystemsinglecomponent.cpp
   skycomponents/solarsystemlistcomponent.cpp
   skycomponents/asteroidscomponent.cpp
   skycomponents/cometscomponent.cpp
   skycomponents/planetmoonscomponent.cpp
   skycomponents/solarsystemcomposite.cpp
   skycomponents/satellitescomponent.cpp
   skycomponents/starcomponent.cpp
   skycomponents/deepstarcomponent.cpp
   skycomponents/deepskycomponent.cpp
   skycomponents/catalogcomponent.cpp
   skycomponents/constellationboundarylines.cpp
   skycomponents/constellationlines.cpp
   skycomponents/constellationnamescomponent.cpp
   skycomponents/supernovaecomponent.cpp
   skycomponents/coordinategrid.cpp
   skycomponents/equatorialcoordinategrid.cpp
   skycomponents/horizontalcoordinategrid.cpp
   skycomponents/ecliptic.cpp
   skycomponents/equator.cpp
   skycomponents/horizoncomponent.cpp
   skycomponents/milkyway.cpp
   skycomponents/skycomponent.cpp
   skycomponents/skycomposite.cpp
   skycomponents/starblock.cpp
   skycomponents/starblocklist.cpp
   skycomponents/starblockfactory.cpp
   skycomponents/culturelist.cpp
   skycomponents/flagcomponent.cpp
   skycomponents/targetlistcomponent.cpp
   skycomponents/notifyupdatesui.cpp
)

set(libkstarswidgets_SRCS
	widgets/clicklabel.cpp
	widgets/dmsbox.cpp
	widgets/draglistbox.cpp
	widgets/fovwidget.cpp
	widgets/logedit.cpp
	widgets/magnitudespinbox.cpp
	widgets/mapcanvas.cpp
	widgets/thumbimage.cpp
	widgets/timespinbox.cpp
	widgets/timestepbox.cpp
	widgets/timeunitbox.cpp
	widgets/infoboxwidget.cpp
	widgets/genericcalendarwidget.cpp
	widgets/moonphasecalendarwidget.cpp
	widgets/kshelplabel.cpp
)

kde4_add_ui_files(libkstarswidgets_SRCS
  widgets/genericcalendarwidget.ui
)

set( kstars_KCFG_SRCS Options.kcfgc )

set(kstars_options_SRCS
  options/opsadvanced.cpp
  options/opscatalog.cpp
  options/opscolors.cpp
  options/opsguides.cpp
  options/opssolarsystem.cpp
  options/opssatellites.cpp
  options/opssupernovae.cpp
)

set(kstars_optionsui_SRCS
  options/opsadvanced.ui
  options/opscatalog.ui
  options/opscolors.ui
  options/opsguides.ui
  options/opssolarsystem.ui
  options/opssatellites.ui
  options/opssupernovae.ui
)

set(kstars_skyobjects_SRCS
  skyobjects/deepskyobject.cpp
  skyobjects/jupitermoons.cpp
  skyobjects/planetmoons.cpp
  skyobjects/ksasteroid.cpp
  skyobjects/kscomet.cpp
  skyobjects/ksmoon.cpp
  skyobjects/ksplanetbase.cpp
  skyobjects/ksplanet.cpp
  skyobjects/kspluto.cpp
  skyobjects/kssun.cpp
  skyobjects/skyline.cpp
  skyobjects/skyobject.cpp
  skyobjects/skypoint.cpp
  skyobjects/starobject.cpp
  skyobjects/trailobject.cpp
  skyobjects/satellite.cpp
  skyobjects/supernova.cpp
)

set(kstars_dialogs_SRCS
  dialogs/addcatdialog.cpp
  dialogs/addlinkdialog.cpp
  dialogs/detaildialog.cpp
  dialogs/finddialog.cpp
  dialogs/focusdialog.cpp
  dialogs/fovdialog.cpp
  dialogs/locationdialog.cpp
  dialogs/timedialog.cpp
  dialogs/exportimagedialog.cpp
)

set(kstars_dialogsui_SRCS
  dialogs/addcatdialog.ui
  dialogs/addlinkdialog.ui
  dialogs/details_database.ui
  dialogs/details_data.ui
  dialogs/details_data_comet.ui
  dialogs/details_links.ui
  dialogs/details_log.ui
  dialogs/details_position.ui
  dialogs/finddialog.ui
  dialogs/focusdialog.ui
  dialogs/fovdialog.ui
  dialogs/locationdialog.ui
  dialogs/wizwelcome.ui
  dialogs/wizlocation.ui
  dialogs/wizdownload.ui
  dialogs/newfov.ui
  dialogs/exportimagedialog.ui
)

set(kstars_projection_SRCS
    projections/projector.cpp
    projections/lambertprojector.cpp
    projections/gnomonicprojector.cpp
    projections/stereographicprojector.cpp
    projections/orthographicprojector.cpp
    projections/azimuthalequidistantprojector.cpp
    projections/equirectangularprojector.cpp
)

set(kstars_extra_SRCS
	colorscheme.cpp	dms.cpp fov.cpp geolocation.cpp
	imageviewer.cpp
	ksfilereader.cpp ksnumbers.cpp
	kspopupmenu.cpp obslistpopupmenu.cpp ksalmanac.cpp
	kstarsactions.cpp kstarsdata.cpp ksuserdb.cpp kstarsdatetime.cpp
	kstarsdcop.cpp kstarsinit.cpp kstars.cpp
	kstarssplash.cpp ksutils.cpp kswizard.cpp main.cpp
	simclock.cpp skymap.cpp skymapdrawabstract.cpp skymapqdraw.cpp skymapevents.cpp
	skypainter.cpp skyqpainter.cpp
	texturemanager.cpp
	timezonerule.cpp
	thumbnailpicker.cpp thumbnaileditor.cpp binfilehelper.cpp
	satellitegroup.cpp
	imageexporter.cpp
)

set(oal_SRCS
    oal/log.cpp
    oal/observer.cpp
    oal/site.cpp
    oal/session.cpp
    oal/scope.cpp
    oal/eyepiece.cpp
    oal/filter.cpp
    oal/observation.cpp
    oal/lens.cpp
    oal/equipmentwriter.cpp
    oal/observeradd.cpp
    oal/execute.cpp
)

set(printing_SRCS
    printing/detailstable.cpp
    printing/finderchart.cpp
    printing/foveditordialog.cpp
    printing/fovsnapshot.cpp
    printing/kstarsdocument.cpp
    printing/legend.cpp
    printing/loggingform.cpp
    printing/printingwizard.cpp
    printing/pwizchartconfig.cpp
    printing/pwizchartcontents.cpp
    printing/pwizfovbrowse.cpp
    printing/pwizfovconfig.cpp
    printing/pwizfovmanual.cpp
    printing/pwizfovsh.cpp
    printing/pwizfovtypeselection.cpp
    printing/pwizobjectselection.cpp
    printing/pwizprint.cpp
    printing/shfovexporter.cpp
    printing/simplefovexporter.cpp
)

set(printingui_SRCS
    printing/foveditordialog.ui
    printing/pwizchartconfig.ui
    printing/pwizchartcontents.ui
    printing/pwizfovbrowse.ui
    printing/pwizfovconfig.ui
    printing/pwizfovmanual.ui
    printing/pwizfovsh.ui
    printing/pwizfovtypeselection.ui
    printing/pwizobjectselection.ui
    printing/pwizprint.ui
    printing/pwizwelcome.ui
)

##set(kstars_SRCS ${indi_SRCS} ${ekos_SRCS} ${fits_SRCS}
set(kstars_SRCS ${indi_SRCS} ${fits_SRCS} ${ekos_SRCS}
	${libkstarswidgets_SRCS} ${libkstarscomponents_SRCS} ${libkstarstools_SRCS}
	${kstars_extra_SRCS}  ${kstars_gl_SRCS} ${kstars_projection_SRCS} ${xplanet_SRCS}
	${kstars_options_SRCS} ${kstars_skyobjects_SRCS} ${kstars_dialogs_SRCS} ${oal_SRCS}
        ${printing_SRCS}
)

qt4_add_dbus_adaptor(kstars_SRCS org.kde.kstars.xml kstars.h KStars)
qt4_add_dbus_adaptor(kstars_SRCS org.kde.kstars.SimClock.xml simclock.h SimClock)

kde4_add_kcfg_files(kstars_SRCS ${kstars_KCFG_SRCS})

##DCOP_IS_DEAD
#kde4_add_dcop_skels(kstars_SRCS kstarsinterface.h simclockinterface.h )

kde4_add_ui_files(kstars_SRCS
       ${indiui_SRCS} ${ui_SRCS} ${fitsui_SRCS} ${ekosui_SRCS} ${xplanetui_SRCS} ${kstars_optionsui_SRCS} ${kstars_dialogsui_SRCS}
       ${printingui_SRCS}
         thumbnailpicker.ui thumbnaileditor.ui oal/observeradd.ui oal/equipmentwriter.ui oal/execute.ui  skycomponents/notifyupdatesui.ui
)

#kde4_add_app_icon(kstars_SRCS "${KDE4_ICON_DIR}/oxygen/*/apps/kstars.png")
#kde4_add_app_icon(kstars_SRCS "${CMAKE_CURRENT_SOURCE_DIR}/ox*-apps-kstars.png")
kde4_add_app_icon(kstars_SRCS "${CMAKE_CURRENT_SOURCE_DIR}/hi*-app-kstars.png")
add_executable(kstars kstars.cpp)
kde4_add_library( KStarsLib STATIC ${kstars_SRCS})

# kde4_add_executable(kstars ${kstars_SRCS})

target_link_libraries(KStarsLib
        LibKSDataHandlers
        ${KDE4_KDECORE_LIBS}
	${KDE4_KNEWSTUFF3_LIBS}
	${KDE4_KIO_LIBS}
    ${QT_QTDECLARATIVE_LIBRARY}
    kdeclarative
	htmesh
	${ZLIB_LIBRARIES}
	${QT_QTSQL_LIBRARY}
        )
# qt4_automoc(kstars.h)
if(NOT WIN32)
  target_link_libraries(KStarsLib m)
endif(NOT WIN32)
if (CFITSIO_FOUND)
  target_link_libraries(KStarsLib ${CFITSIO_LIBRARIES})
endif (CFITSIO_FOUND)
if (INDI_FOUND)
  target_link_libraries(KStarsLib ${INDI_LIBRARIES} ${INDI_CLIENT_LIBRARIES} z)
endif (INDI_FOUND)
if (WCSLIB_FOUND)
    target_link_libraries(KStarsLib ${WCSLIB_LIBRARIES})
endif (WCSLIB_FOUND)

if( OPENGL_FOUND )
    target_link_libraries(KStarsLib
    ${OPENGL_LIBRARIES}
    ${QT_QTOPENGL_LIBRARY}
    )
endif( OPENGL_FOUND )


target_link_libraries(kstars KStarsLib)

install(TARGETS kstars ${INSTALL_TARGETS_DEFAULT_ARGS})


########### install files ###############
install( PROGRAMS kstars.desktop  DESTINATION  ${XDG_APPS_INSTALL_DIR} )
install( FILES kstars.kcfg  DESTINATION  ${KCFG_INSTALL_DIR} )
install( FILES kstars.knsrc  DESTINATION  ${CONFIG_INSTALL_DIR} )
if (INDI_FOUND)
install( FILES kstarsui-indi.rc DESTINATION  ${DATA_INSTALL_DIR}/kstars/ RENAME kstarsui.rc)
else (INDI_FOUND)
install( FILES kstarsui.rc DESTINATION  ${DATA_INSTALL_DIR}/kstars/ )
endif(INDI_FOUND)

install( FILES fitsviewer.rc  DESTINATION  ${DATA_INSTALL_DIR}/kstars/ )
if (WIN32)
  install( FILES kstarsui-win.rc  DESTINATION  ${DATA_INSTALL_DIR}/kstars/ )
endif (WIN32)

kde4_install_icons( ${ICON_INSTALL_DIR}   )
