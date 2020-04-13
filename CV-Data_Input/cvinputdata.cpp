//By Samuel PP Silveira, Centro Federal de Educação Tecnológica de Minas Gerais, 2017

#include "cvinputdata.h"
#include "ui_cvinputdata.h"
#include <QDebug>
#include <QFile>
#include <QDateTime>
#include <QTextStream>
#include <QDir>
#include <iostream>
#include <stdio.h>
#include <QProcess>
#include <cmath>
#include <string>
#include <cstdlib>
#include <QSplashScreen>

using namespace std;

CVInputData::CVInputData(QWidget *parent) :
QMainWindow(parent),
ui(new Ui::CVInputData) {
    ui->setupUi(this);
}

CVInputData::~CVInputData() {
    delete ui;
}

void Parameters::writeParameters() {
    QFile file(getOutFileName());

    if (!file.open(QFile::WriteOnly | QFile::Text)) {
        qDebug() << "Error, file couldn't be created!\n";
        return;
    }
    QTextStream word(&file);

    word << "# Lines with an initial # need not contain an =\n"
            "# Lines with an initial 'backslash n'(i.e., empty lines) are allowed.\n"
            "# All other lines must contain an '=' sign, and it must occur before any\n"
            "# (optional) '#'.  The part of the line after the '#' is ignored.\n"
            "# Don't use '#' or '=' as part of a label name.\n\n"
            "# Except where numerically keyed selections are in use, '0' (zero) means no, and '1' (one) means yes.\n"
            "\n\nVERBOSE			=" << verbose << "		# Put the number of a code listed below to control verbose output.\n"
            "# 0:NONE,1:SURFACE,2:DIAG,3:FIELD,4:VELTABLE,5:INT,6:JBAR,7:GRAD,8:SOURCE,9:PROFILE,10:SOURCESURFACE,11:GRID,12:CROSSING,13:MONITOR \n"
            "# Warning: using 2:DIAG for a normally dimensioned job can easily fill a disk.\n"
            "AUXVERBOSE		=" << auxverbose << "		# Put the number of a code listed below to control verbose output for special point.\n"
            "SPECIAL_I		=" << specialI << "		# The 'i' index of the source grid point where AUXVERBOSE level will be used. (-1 => don't use)\n"
            "SPECIAL_J		=" << specialJ << "		# The 'j' index of the source grid point where AUXVERBOSE level will be used. (-1 => don't use)\n\n\n"
            "VELOCITY_LAW		=" << velocityLaw << "		# Put the number of a code listed below to select a cv model.\n"
            "# Velocity law also dictates the geometry: 0:RADIAL,1:MAGNETO,2:INFALL,3:HUMMER,4:ROTMAGNETO,5:MAGNETOTABLE,6:DISKWIND,7:MAGNETO + DISKWIND\n\n"
            "ATMOSPHERE_TYPE		=" << atmosphereType << "		# 0:Blackbody,1:Atmosphere\n\n"
            "# Indicate what phase of a cv job you want to run by selecting one of the codes listed in the accompanying comment.\n"
            "JOB_TYPE		=" << jobType << "		# 0:ignore, 1:surface, 2:source, 3:profile, 4:ioneql, 5:makegrid\n\n"
            "USE_GRID_FILE		=" << useGridFile << "		# Use the information in GRID_FILENAME for densities and temperatures over the grid.\n"
            "USE_TEMPERATURES_ONLY	=" << useTemperaturesOnly << "		# Use the information in GRID_FILENAME only for temperatures over the grid.\n"
            "GRID_FILENAME		=" << gridFilename << "	# A file of densities and temperatures over the grid.\n"
            "SURFACES_FILENAME	=" << surfacesFilename << "	# A file of binary surface information.\n"
            "VELOCITY_FILENAME	=" << velocityFilename << "	# A file of velocity data, currently used in MAGNETOTABLE and DISKWIND\n"
            "PROF_VEL_FILENAME	=" << profVelFilename << "	# A file of a list of velocities at which line profile intensities are to be found.\n"
            "ATMOSPHERE_FILENAME	=" << atmosphereFilename << "       # A file containing the frequencies and fluxes emitted from the star.\n\n\n"
            "# Physical parameters.\n"
            "STELLAR_RAD_IN_RSUN	=" << stellarRadInRsun << "		# Stellar radius in Rsun.\n"
            "STELLAR_MASS_IN_MSUN	=" << stellarMassInMsun << "		# Stellar mass in Msun.\n"
            "MAX_RADIUS		=" << maxRadius << "		# All computation occurs within this number of stellar radii,\n"
            "#					  unless overridden by DISKWIND outer corner, or OUTER_R0.\n"
            "TEMP_STAR		=" << tempStar << "		# Temperature of stellar photosphere.\n"
            "TEMP_RING		=" << tempRing << "		# Only consulted in magnetosphere cases.\n"
            "RADIATION_TEMP		=" << radiationTemp << "		# For IONEQL.\n"
            "TEMP_GAS		=" << tempGas << "		# Ignored if USE_GRID_FILE or USE_TEMPERATURES_ONLY is yes.\n"
            "FIXED_EPSILON		=" << fixedEpsilon << "		# Set this to negative to disable.\n\n\n"
            "# Atomic parameters when using atom file (currently when and only when ELEMENT==1).\n"
            "USE_ATOM_FILE		=" << useAtomFile << "		# 1 means yes, 0 means no.\n"
            "DO_MULTI		=" << doMulti << "		# 1 means yes, 0 means no.  Multi means derive source from n(lower), n(upper).\n"
            "ELEMENT			=" << element << "		# Use the atomic number.\n"
            "ATOM_FILENAME		=" << atomFilename << "	# The name of the file containing atomic parameters.\n"
            "LOWERLEVEL		=" << lowerLevel << " 		# For H\n"
            "UPPERLEVEL		=" << upperLevel << "		# For H\n\n"
            "# Line values needed if not using atom file.\n"
            "ABUNDANCE		=" << abundance << "		# Set this fudge factor to one if using atom file.\n"
            "OSCILLATOR		=" << oscillator << "		# \n"
            "C_UPPERLEVEL		=" << cUpperlevel << "	# \n"
            "A_UPPERLEVEL		=" << aUpperlevel << "		# \n"
            "FREQUENCY		=" << frequency << "		# If zero, determine from WAVELENGTH.\n"
            "WAVELENGTH		=" << wavelenght << "	# cm \n\n"
            "# Parameters to control photospheric profile:\n"
            "# correction=1-LINE_DEPTH*((1-LINE_WING)*exp(-x*x)+LINE_WING/((1+x)**2)),\n"
            "# x=v/LINE_DOPPLER_WIDTH, v=velocity from line center.\n"
            "LINE_DEPTH		=" << lineDepth << "		# \n"
            "LINE_DOPPLER_WIDTH	=" << lineDopplerWidth << "	        # km/s \n"
            "LINE_WING		=" << lineWing << "		# \n\n"
            "# Used in magnetosphere and diskwind.\n"
            "SUPPRESS_ROTATION	=" << suppressRotation << "		# \n"
            "DO_HOTSPOT              =" << doHotspot << "               # \n"
            "HOTSPOTPHI1             =" << hotspotphi1 << "             # in degrees\n"
            "HOTSPOTPHI2             =" << hotspotphi2 << "             # in degrees \n\n"
            "# Used in diskwind\n"
            "DISKWIND_INNER_X0	=" << diskwindInnerXo << "		#\n"
            "DISKWIND_OUTER_X0	=" << diskwindOuterXo << " 		#\n"
            "DISKWIND_Z_HEIGHT       =" << diskwindZHeight << "           #\n"
            "DISKWIND_A              =" << diskwindA << "          # \n"
            "DISKWIND_B              =" << diskwindB << "         # \n"
            "DISKWIND_RHO0           =" << diskwindRho0 << "      # \n"
            "DISKWIND_TDMAX		=" << diskwindTdmax << "		# \n\n"
            "# Magnetosphere stuff.\n"
            "DENSITY_FACTOR		=" << densityFactor << "		# Densities in MAGNETOTABLE velocity table get multiplied by this.\n"
            "MASS_FLOW		=" << massFlow << "	# gm/s, this is the handle on densConst.\n"
            "INNER_R0		=" << innerR0 << "		# radius where inner field line intersects disk plane.\n"
            "OUTER_R0		=" << outerR0 << "   	# radius where outer field line intersects disk plane.\n"
            "BEQ			=" << beq << "		# equatorial stellar magnetic field in Gauss.\n"
            "POL_VEL_INNER		=" << polVelInner << "		# initial poloidal velocity on the inner field line in units of (G*Mstar/Rstar). \n"
            "OMEGASK			=" << omegask << "		# ratio of omega(star) to omega(Keplerian). \n"
            "XLIN			=" << xlin << "		# specific angular momentum for the inner field line in units of (G*Mstar/Rstar)^(1/2). \n\n"
            "# Rybicki and Hummer stuff\n"
            "RH_TAU0			=" << rhTau0 << "		# \n\n"
            "# Source function dimensions.\n"
            "MAX_ITERATION		=" << maxIteration << "		# See cvdim.h for maximum allowable dimensions.\n"
            "NSOURCE_X		=" << nSourceX << "		#\n"
            "NSOURCE_Z		=" << nSourceZ << " 		# \n"
            "NSOURCE_PHI		=" << nSourcePhi << "		# \n"
            "NSOURCE_THETA		=" << nSourceTheta << "		#\n"
            "NSOURCE_STEP		=" << nSourceStep << "            # This parameter is overridden in magnetosphere case.\n"
            "SOURCE_THETASTAR_FRAC	=" << sourceThetastarFrac << "		# Number of rays on star is NSOURCE_THETA/SOURCE_THETASTAR_FRAC.\n\n"
            "# Profile dimensions.\n"
            "PROF_VEL_FACTOR		=" << profVelFactor << "		# If negative, scale values in PROF_VEL_TABLE by max velocity\n"
            "NPROFILE_VELOCITY	=" << nprofileVelocity << "		# \n"
            "NPROFILE_ANGLE		=" << nprofileAngle << "		# \n"
            "NPROFILE_RADII		=" << nprofileRadii << "		# This is the total number of radii, including NPROFILE_STAR_RADII.\n"
            "NPROFILE_STAR_RADII	=" << nprofileStarRadii << "		# \n"
            "NPROFILE_STEP		=" << nprofileStep << "		# This parameter is overridden in magnetosphere case.\n"
            "FIRST_VELOCITY		=" << firstVelocity << "		# km/s\n"
            "LAST_VELOCITY		=" << lastVelocity << "		# \n"
            "INCLINATION		=" << inclination << "		# 90o is equator-on, 0o is pole-on.  Ordinarily control using -i command line.\n\n"
            "# Can use these with JOB_TYPE 0, ordinarily JOB_TYPE!=0 overrides these.\n"
            "USE_SAVED_SURFACES	=" << usedSavedSurfaces << "		# 0 means don't use SURFACES_FILENAME as a surface file, 1 means do.\n"
            "SAVE_SURFACES		=" << saveSurfaces << "		# \n"
            "USE_SAVED_SOURCE	=" << useSavedSource << "		# 0 means don't use SOURCE_NAME as source function, 1 means do.\n"
            "SAVE_SOURCE		=" << saveSource << "		# 0 means don't save source function to SOURCE_NAME (overwrites), 1 means do.\n"
            "DO_PROFILE		=" << doProfile << "		# \n"
            "DO_IONEQL		=" << doIoneql << "		#\n";

    file.flush();
    file.close();
    return;
}

void Parameters:: printConfigFile(){
    qDebug() <<
            "VERBOSE			=" << verbose <<
            "\nAUXVERBOSE		=" << auxverbose <<
            "\nSPECIAL_I		=" << specialI <<
            "\nSPECIAL_J		=" << specialJ <<
            "\nVELOCITY_LAW		=" << velocityLaw <<
            "\nATMOSPHERE_TYPE		=" << atmosphereType <<
            "\nJOB_TYPE		=" << jobType <<
            "\nUSE_GRID_FILE		=" << useGridFile <<
            "\nUSE_TEMPERATURES_ONLY	=" << useTemperaturesOnly <<
            "\nGRID_FILENAME		=" << gridFilename <<
            "\nSURFACES_FILENAME	=" << surfacesFilename <<
            "\nVELOCITY_FILENAME	=" << velocityFilename <<
            "\nPROF_VEL_FILENAME	=" << profVelFilename <<
            "\nATMOSPHERE_FILENAME	=" << atmosphereFilename <<

            "\n\nPhysical parameters.\n"
            "STELLAR_RAD_IN_RSUN	=" << stellarRadInRsun <<
            "\nSTELLAR_MASS_IN_MSUN	=" << stellarMassInMsun <<
            "\nMAX_RADIUS		=" << maxRadius <<
            "\nTEMP_STAR		=" << tempStar <<
            "\nTEMP_RING		=" << tempRing <<
            "\nRADIATION_TEMP		=" << radiationTemp <<
            "\nTEMP_GAS		=" << tempGas <<
            "\nFIXED_EPSILON		=" << fixedEpsilon <<
            "\n\nAtomic parameters when using atom file (currently when and only when ELEMENT==1).\n"
            "\nUSE_ATOM_FILE		=" << useAtomFile <<
            "\nDO_MULTI		=" << doMulti <<
            "\nELEMENT			=" << element <<
            "\nATOM_FILENAME		=" << atomFilename <<
            "\nLOWERLEVEL		=" << lowerLevel <<
            "\nUPPERLEVEL		=" << upperLevel <<
            "\n\n Line values needed if not using atom file.\n"
            "ABUNDANCE		=" << abundance <<
            "\nOSCILLATOR		=" << oscillator <<
            "\nC_UPPERLEVEL		=" << cUpperlevel <<
            "\nA_UPPERLEVEL		=" << aUpperlevel <<
            "\nFREQUENCY		=" << frequency <<
            "\nWAVELENGTH		=" << wavelenght <<
            "\n\n Parameters to control photospheric profile:\n"
            "\nLINE_DEPTH		=" << lineDepth <<
            "\nLINE_DOPPLER_WIDTH	=" << lineDopplerWidth <<
            "\nLINE_WING		=" << lineWing <<
            "\n\n Used in magnetosphere and diskwind.\n"
            "SUPPRESS_ROTATION	=" << suppressRotation <<
            "\nDO_HOTSPOT              =" << doHotspot <<
            "\nHOTSPOTPHI1             =" << hotspotphi1 <<
            "\nHOTSPOTPHI2             =" << hotspotphi2 <<
            "\n\n Used in diskwind\n"
            "DISKWIND_INNER_X0	=" << diskwindInnerXo <<
            "\nDISKWIND_OUTER_X0	=" << diskwindOuterXo <<
            "\nDISKWIND_Z_HEIGHT       =" << diskwindZHeight <<
            "\nDISKWIND_A              =" << diskwindA <<
            "\nDISKWIND_B              =" << diskwindB <<
            "\nDISKWIND_RHO0           =" << diskwindRho0 <<
            "\nDISKWIND_TDMAX		=" << diskwindTdmax <<
            "\n\n Magnetosphere stuff.\n"
            "DENSITY_FACTOR		=" << densityFactor <<
            "\nMASS_FLOW		=" << massFlow <<
            "\nINNER_R0		=" << innerR0 <<
            "\nOUTER_R0		=" << outerR0 <<
            "\nBEQ			=" << beq <<
            "\nPOL_VEL_INNER		=" << polVelInner <<
            "\nOMEGASK			=" << omegask <<
            "\nXLIN			=" << xlin <<
            "\n\n Rybicki and Hummer stuff\n"
            "RH_TAU0			=" << rhTau0 <<
            "\n\n Source function dimensions.\n"
            "MAX_ITERATION		=" << maxIteration <<
            "\nNSOURCE_X		=" << nSourceX <<
            "\nNSOURCE_Z		=" << nSourceZ <<
            "\nNSOURCE_PHI		=" << nSourcePhi <<
            "\nNSOURCE_THETA		=" << nSourceTheta <<
            "\nNSOURCE_STEP		=" << nSourceStep <<
            "\nSOURCE_THETASTAR_FRAC	=" << sourceThetastarFrac <<
            "\n\n Profile dimensions.\n"
            "PROF_VEL_FACTOR		=" << profVelFactor <<
            "\nNPROFILE_VELOCITY	=" << nprofileVelocity <<
            "\nNPROFILE_ANGLE		=" << nprofileAngle <<
            "\nNPROFILE_RADII		=" << nprofileRadii <<
            "\nNPROFILE_STAR_RADII	=" << nprofileStarRadii <<
            "\nNPROFILE_STEP		=" << nprofileStep <<
            "\nFIRST_VELOCITY		=" << firstVelocity <<
            "\nLAST_VELOCITY		=" << lastVelocity <<
            "\nINCLINATION		=" << inclination <<
            "\n\n Can use these with JOB_TYPE 0, ordinarily JOB_TYPE!=0 overrides these.\n"
            "USE_SAVED_SURFACES	=" << usedSavedSurfaces <<
            "\nSAVE_SURFACES		=" << saveSurfaces <<
            "\nUSE_SAVED_SOURCE	=" << useSavedSource <<
            "\nSAVE_SOURCE		=" << saveSource <<
            "\nDO_PROFILE		=" << doProfile <<
            "\nDO_IONEQL		=" << doIoneql ;

}

void Parameters::run(){
    //Getting the time stamp
    QDateTime _time_now = QDateTime::currentDateTime();
    QString _time_path = _time_now.toString("yyyyMM");
    QString _time_stamp = _time_now.toString("dd_hhmmss");
    _time_stamp = _time_path + _time_stamp;
    qDebug()<<"Beginning time:"<< _time_now.toString("h:m:s:zzz dd/MM/yyyy")<<endl;

    //declaring constants
    const double G_CONST = 6.67408e-11; // gravitational constant (m^3 kg^-1 s^-2)
    const double M_SUN = 1.98892e30;  // solar mass (kg)
    const double R_SUN = 6.955e8;      // solar radius (m)

    //cout<<G_CONST<<" "<< M_SUN << " "<<R_SUN<<endl;

    //declaring strings with the path of the programs to be called

    QString WORKDIR = "/home/samuel/Documents/CV/";
    QString PATHOUT = WORKDIR + "CV_OUTPUT/";

    QString BASECONFIG = WORKDIR + "cvmod/newconfig." + nameStar;
    //qDebug()<<nameStar;
    QString INBP = WORKDIR + "cvmod/wind/inbp";
    QString CV = WORKDIR+"cvmod/cv";
    QString FIX = WORKDIR+"flux/fix";
    QString FLUX = WORKDIR+"flux/flux";
    QString GRIDOUT = WORKDIR+"flux/gridout";
    QString HYDRO = WORKDIR + "hydro/hydro_cv8l";
    QString SAMPLING = WORKDIR + "flux/sampling.py";
    QString TTEMP = WORKDIR + "cvmod/Temp/temperature";
    QString CV_OUTPUT = "grid.dat";
    QString DENS_COMP = WORKDIR+"cvmod/Dens/dens_compensation";
    QString PLOT = WORKDIR + "flux/gauss_plot.py";
    QString _QUERYBASE = "java -jar " + WORKDIR + "cvmod/CVDBConnector/dist/CV_DataBase.jar";
    //reading disk wind self-similar solution input parameters

    QFile input_bp(INBP);

    if(!input_bp.open(QFile::ReadOnly | QFile::Text) )
    {
        // It could not open
        QMessageBox::warning(NULL,"Abort", "INBP failed to open!\n");
        return;
    }

    QTextStream bp_allFile(&input_bp);
    QString bp_allString;
    bp_allString.append(bp_allFile.readAll());
    bp_allString = bp_allString.simplified();
    //qDebug()<<bp_allString<<endl;
    int bp_npoints = bp_allString.section(" ", 0,0).toInt();
    //cout<<bp_npoints<<endl;
    float bp_zmax = bp_allString.section(" ",1,1).toFloat();
    //cout<<bp_zmax<<endl;
    float bp_a = bp_allString.section(" ",2,2).toFloat();
    cout<<"bp a "<<bp_a<<endl;
    float bp_b = bp_allString.section(" ",3,3).toFloat();
    cout<<bp_b<<endl;
    float bp_kappa = bp_allString.section(" ",4,4).toFloat();
    //cout<<bp_kappa<<endl;
    float bp_lambda = bp_allString.section(" ",5,5).toFloat();
    //cout<<bp_lambda<<endl;
    input_bp.close();


    //reading parameters from CV configuration file
    int USE_ATMOSPHERE = atmosphereType.toInt();
    //cout<<"Use Atmosphere "<<USE_ATMOSPHERE<<endl;
    float MSTAR = stellarMassInMsun.toFloat();
    //cout<<"Mstar: "<<MSTAR<<endl;
    float RSTAR = stellarRadInRsun.toFloat();
    //cout<<"RSTAR: "<<RSTAR<<endl;
    float PHOT_TEMP = tempStar.toFloat();
    //cout<<"PHOT TEMP: "<<PHOT_TEMP<<endl;
    float RING_TEMP = tempRing.toFloat();
    //cout<<"RING TEMP: "<<RING_TEMP<<endl;
    QString DISKWIND_FILE = WORKDIR + "cvmod/" + velocityFilename;
    QString ATMO_FILE = atmosphereFilename;

    int L_LEVEL = lowerLevel.toInt();
    int U_LEVEL = upperLevel.toInt();

    float MAG_INNER_RADIUS = innerR0.toFloat();
    float MAG_OUTER_RADIUS = outerR0.toFloat();
    float MASS_ACC_RATE = massFlow.toFloat();
    MASS_ACC_RATE = MASS_ACC_RATE * 365.242199 * 86400. / (M_SUN*1000.);

    float DWIND_INNER_RADIUS = diskwindInnerXo.toFloat();
    //cout<<"DWIND_INNER_RADIUS: "<<DWIND_INNER_RADIUS<<endl;
    float DWIND_OUTER_RADIUS = diskwindOuterXo.toFloat();
    //cout<<"DWIND_OUTER_RADIUS: "<<DWIND_OUTER_RADIUS<<endl;
    float DWIND_ZMAX = diskwindZHeight.toFloat();
    //cout<<"DWIND_ZMAX: "<<DWIND_ZMAX<<endl;
    float DWIND_DENSITY = diskwindRho0.toFloat();
    //cout<<"DWIND_DENSITY: "<<DWIND_DENSITY<<endl;
    float DWIND_A = diskwindA.toFloat();
    //cout<<"DWIND_A: "<<DWIND_A<<endl;
    float DWIND_B = diskwindB.toFloat();
    //cout<<"DWIND_B: "<<DWIND_B<<endl;

    //On Python script INCL = option.inclination and then casting IINC = int(INCL)
    float FINC = starDiskInclination;      //system inclination in degrees (Given as input.)
    int IINC = FINC;
    //cout<<"IINC 1: "<<IINC<<endl;
    //In Python:

    //MAG_HEATING_RATE = option.mag_heating		#magnetospheric heating rate
    //DWIND_HEATING_RATE = option.wind_heating 	#disk wind heating rate
    //DWIND_TEMP = option.wind_temp			#disk wind isothermal temperature
    //LOWEST_DWIND_TEMP = option.wind_lower		#disk wind lowest possible temperature

    const double TRANS_FREQ = 4.5668e14;   //line center frequency (Hz)

    const double DX = 0.05;                //grid spacing in X direction in the new resampled grid
    const double DZ = 0.05;                //grid spacing in Z direction in the new resampled grid
    const int NCORE = 10;                  //number of core radii
    const int NMAG = 20;                   //number of magnetospheric radii
    const int NDWIND = 100;                 //number of disk wind radii
    const int NFREQ = 81;                  //number of frequencies
    const double RMAX = 190.000;           //maximum distance from the star in stellar radius units
    const float SPHI0 = 0.;
    const double DELSPHI = 3.14159;
    const int NSPHI = 1;
    const int DO_DISKWIND = 1;             //0: no disk wind, 1: disk wind
    const int DO_ROTATION = 1;             //if 0 changes the rotation velocities to zero

    //calculating mass loss rate
    QFile input_diskwind(DISKWIND_FILE);
    if(!input_diskwind.open(QFile::ReadOnly | QFile::Text) )
    {
        // It could not open
        QMessageBox::warning(NULL,"Abort", "Disk Wind File Failed to Open!\n");
        return;
    }
    QTextStream input_diskwind_stream(&input_diskwind);
    QString input_diskwind_string;
    input_diskwind_string.append(input_diskwind_stream.readLine());
    //qDebug()<< input_diskwind_string;
    double diskwind_vz0 = input_diskwind_string.section("  ",2,2).toDouble();
    //printf("Diskwind vz0: %e", diskwind_vz0);
    double diskwind_vx0 = input_diskwind_string.section("  ",3,3).toDouble();
    //printf("Diskwind vx0: %e", diskwind_vx0 );
    double vp_0 = sqrt(pow(diskwind_vx0,2) + pow(diskwind_vz0,2));
    //printf("vp0: %e", vp_0);
    //printf("R sun: %e M: %e",RSTAR, MSTAR);
    double vz_0 = diskwind_vz0;
    const double CONST = G_CONST * M_SUN * MSTAR * pow(R_SUN*RSTAR, 3);

    double LNC = log(DWIND_OUTER_RADIUS/DWIND_INNER_RADIUS);

    double M_LOSS_RATE = 2.00*1000.*DWIND_DENSITY*3.141592*vz_0*sqrt(CONST) * LNC; // kg s^-1
    M_LOSS_RATE = M_LOSS_RATE * 365.24199 * 86400.00 / M_SUN;                     //M_SUN * yr^-1
    //printf("%e %e %e %e", CONST, LNC, DWIND_DENSITY,vz_0);
    printf("M LOSS RATE: %e\n", M_LOSS_RATE);
    //calculating lauching angle
    double DWIND_LAUNCH_ANGLE = atan(2*DWIND_A + DWIND_B)*180./3.141592;

    //declaring the output filenames

    QString _PATHOUT = PATHOUT + nameStar + "/" + _time_path + "/";
    //qDebug()<<"PathOut:"<<_PATHOUT<<endl;
    QString _IONEQL = _PATHOUT + "grid."+nameStar+".ioneql";
    //qDebug()<<"IONEQL:"<<_IONEQL<<endl;
    QString _NHTOTAL = _PATHOUT + "grid." + nameStar + ".nhtotal";
    //qDebug()<<"NHTOTAL:"<<_NHTOTAL<<endl;
    QString _TEMPONLY = _PATHOUT + "grid." + nameStar + ".temponly";
    //qDebug()<<"Temp Only:"<<_TEMPONLY<<endl;
    QString _TEMP_MAXMIN = _PATHOUT + _time_stamp + "_" + nameStar + "_max_min_temp.dat";
    //qDebug()<<"Temp Max Min:"<<_TEMP_MAXMIN<<endl;
    QString _SOURCE = _PATHOUT + _time_stamp + "_grid." + nameStar + ".source";
    //qDebug()<<"Source:"<<_SOURCE<<endl;
    QString _HYDRO = _PATHOUT + _time_stamp + "_grid.8l" + nameStar + ".source";
    //qDebug()<<"Hydro:"<<_HYDRO<<endl;
    QString _TEMP = _PATHOUT + "temp." + CV_OUTPUT;
    //qDebug()<<"Temp:"<<_TEMP<<endl;
    QString _FIXIN = _TEMP + ".rsmpl";
    //qDebug()<<"Fix In:"<<_FIXIN<<endl;
    QString _FIXOUT = _HYDRO + ".rsmpl";
    //qDebug()<<"Fix Out:"<<_FIXOUT<<endl;
    QString _GRIDSIZE = _PATHOUT + _time_stamp + "_gridsize." + nameStar + ".dat";
    //qDebug()<<"Grid Size:"<<_GRIDSIZE<<endl;
    QString _PARAM = _PATHOUT + _time_stamp + "_parameters." + nameStar + ".dat";
    //qDebug()<<"Param:"<<_PARAM<<endl;
    QString _FLUXINPUTTABLE;
    QString _EXISTSDB = WORKDIR+"cvmod/StarExists."+_time_stamp;


    if(USE_ATMOSPHERE){
        _FLUXINPUTTABLE = WORKDIR + "flux/velIntensTable";
    }else{
        _FLUXINPUTTABLE = WORKDIR + "flux/profveltable";
    }
    //qDebug()<<"Flux Input Table:"<<_FLUXINPUTTABLE<<endl;
    //cout<<"IINC: "<<IINC<<endl;
    //qDebug()<<"Inclination" << starDiskInclination<<endl;
    QString _PROFILE = _PATHOUT + _time_stamp + "_prof.Ha."+ QString::number(IINC) + "." + nameStar + ".dat";
    //qDebug()<<"Profile:"<<_PROFILE<<endl;
    QString _INTENSMAP = _PATHOUT + _time_stamp + "_intensmap.Ha." + QString::number(IINC) + "." + nameStar + ".dat";
    //qDebug()<<"Intens Map:"<<_INTENSMAP<<endl;


    //check for the existence or create the PATH where the output files should be written
    QDir CVDir(_PATHOUT);

    if(!CVDir.exists()){
        if(!doSurface){
           QMessageBox::warning(NULL,"Abort", "There's no grid file already made, you have to select the doSurface option!\n");
           return;
        }
        CVDir.mkpath(_PATHOUT);
        cout<<_PATHOUT.toStdString()<<" created."<<endl;
    }else{
        cout<<_PATHOUT.toStdString()<<" already exists."<<endl;
    }

    //creating temperature input options
    //cout<<"TempType"<<tempType<<endl;
    QString TEMPTYPE, TEMPINPUT;

    //cout<<"TempType"<<tempType<<endl;
    switch(tempType){
    case 1:
        TEMPTYPE = "Only magnetosphere.";
        TEMPINPUT = _NHTOTAL + "\n" + _TEMP_MAXMIN + "\n" + QString::number(tempType) + "\n" + QString::number(magnetoHeatingRate) + "\n" + _TEMPONLY + "\n";
        break;
    case 2:
        TEMPTYPE = "Only disk wind.";
        TEMPINPUT = (_NHTOTAL + "\n" + _TEMP_MAXMIN + "\n" + QString::number(tempType) + "\n" + QString::number(diskwindHeatingRate) + "\n" + _TEMPONLY + "\n");
        break;
    case 3:
        TEMPTYPE = "Only disk wind with a given minimum temperature.";
        TEMPINPUT = (_NHTOTAL + "\n" + _TEMP_MAXMIN + "\n" +  QString::number(tempType) + "\n" + QString::number(diskwindHeatingRate) + "\n" + QString::number(diskwindMinTemperature) + "\n" + _TEMPONLY + "\n");
        break;
    case 4:
        TEMPTYPE = "Only an isothermal disk wind.";
        TEMPINPUT = (_NHTOTAL + "\n" + _TEMP_MAXMIN + "\n" +  QString::number(tempType) + "\n" + QString::number(diskwindTemp) + "\n" + _TEMPONLY + "\n");
        break;
    case 5:
        TEMPTYPE = "Magnetosphere and disk wind";
        TEMPINPUT = (_NHTOTAL + "\n" + _TEMP_MAXMIN + "\n" +  QString::number(tempType) + "\n" + QString::number(magnetoHeatingRate) + "\n" + QString::number(diskwindHeatingRate) + "\n" + _TEMPONLY + "\n");
        break;
    case 6:
        TEMPTYPE = "Magnetosphere and disk wind with a given minimum temperature.";
        TEMPINPUT = (_NHTOTAL + "\n" + _TEMP_MAXMIN + "\n" +  QString::number(tempType) + "\n" + QString::number(magnetoHeatingRate) + "\n" + QString::number(diskwindHeatingRate) + "\n" + QString::number(diskwindMinTemperature) + "\n" + _TEMPONLY + "\n");
        break;
    case 7:
        TEMPTYPE = "Magnetosphere and isothermal disk wind.";
        TEMPINPUT = (_NHTOTAL + "\n" + _TEMP_MAXMIN + "\n" +  QString::number(tempType) + "\n" + QString::number(magnetoHeatingRate) + "\n" + QString::number(diskwindTemp) + "\n" + _TEMPONLY + "\n");
        //cout<<"Caso 7"<<TEMPINPUT.toStdString()<<endl;
        break;
    default:
        QMessageBox::warning(NULL,"Abort", "There's no Temperature Input!\n");
        return;
    }

    //cout<<"TEMP INPUT: "<< TEMPINPUT.toStdString();

    //creating other codes input arguments

    QString DESINPUT_I = _NHTOTAL + "\n" + _NHTOTAL + "\n";
    QString DESINPUT_II = _IONEQL + "\n" + _IONEQL + "\n";
    QString HYDROINPUT = _SOURCE + "\n" + _HYDRO + "\n";
    QString GRIDOUTINPUT = (_HYDRO + "\n" + _HYDRO + "\n" + QString::number(L_LEVEL) + " " + QString::number(U_LEVEL) + "\n" + QString::number(MSTAR) + ", " + QString::number(RSTAR) + "\n" + QString::number(DO_ROTATION) + "\n");
    QString FIXINPUT = (_FIXIN + "\n" + _FIXOUT + "\n" + QString::number(MAG_INNER_RADIUS) + "\n" + QString::number(MAG_OUTER_RADIUS) + "\n" + QString::number(DWIND_INNER_RADIUS) + "\n" + QString::number(DWIND_OUTER_RADIUS) + "\n" + QString::number(DWIND_A) + "\n" + QString::number(DWIND_B) + "\n");
    QString FLUXINPUT = (_FIXOUT+"\n" + _GRIDSIZE+"\n" + QString::number(MSTAR)+"\n" +  QString::number(RSTAR)+"\n" +  QString::number(USE_ATMOSPHERE)+"\n" +
                          QString::number(PHOT_TEMP)+"\n" +  QString::number(RING_TEMP)+"\n" +  QString::number(TRANS_FREQ)+"\n" +  QString::number(IINC)+"\n" +
                          QString::number(NCORE)+"\n" +  QString::number(NMAG)+"\n" +  QString::number(MAG_INNER_RADIUS)+"\n" +  QString::number(MAG_OUTER_RADIUS)+"\n" +
                          QString::number(DO_DISKWIND)+"\n" +  QString::number(NDWIND)+"\n" +  QString::number(DWIND_INNER_RADIUS)+"\n" +  QString::number(DWIND_OUTER_RADIUS)+"\n" +
                          QString::number(RMAX)+"\n" +  QString::number(U_LEVEL) +" "+  QString::number(L_LEVEL) +"\n" + _FLUXINPUTTABLE+"\n" + _PROFILE+"\n" +
                         _INTENSMAP+"\n" +  QString::number(NFREQ)+"\n" +  QString::number(SPHI0) +" "+  QString::number(DELSPHI) +" "+  QString::number(NSPHI) +"\n");
    //cout<<"DESINPUT_I: "<<DESINPUT_I.toStdString()<<endl;
    //cout<<"DESINPUT_II: "<<DESINPUT_II.toStdString()<<endl;
    //cout<<"HYDROINPUT: "<<HYDROINPUT.toStdString()<<endl;
    //cout<<"GRIDOUTINPUT: "<<GRIDOUTINPUT.toStdString()<<endl;
    //cout<<"FIXINPUT: "<<FIXINPUT.toStdString()<<endl;
    //cout<<"FLUXINPUT: "<<FLUXINPUT.toStdString()<<endl;

    //declaring arguments for each CV pass
    QString cv_command_line1 =" -J 5 -v 0";
    QStringList cv_args1 = cv_command_line1.split(" ");
    //qDebug()<<"CV Args1: "<< cv_args1.toStdList()<<endl;

    QString cv_command_line3 = " -J 4 -v 0 -G " + _TEMPONLY;
    QStringList cv_args3 = cv_command_line3.split(" ");
    //qDebug()<<"CV Args3: "<< cv_args3.toStdList()<<endl;

    QString cv_command_line4 = " -J 2 -v 0 -G " + _IONEQL;
    QStringList cv_args4 = cv_command_line4.split(" ");
    //qDebug()<<"CV Args4: "<< cv_args4.toStdList()<<endl;

    //declaring arguments for sampling.py

    QString sampling_command = " --file " + _TEMP + " -x " + QString::number(DX) + " -y " + QString::number(DZ);
    //cout<<"Sampling command: "<<sampling_command.toStdString()<<endl;
    QStringList sampling_args = sampling_command.split(" ");

    //declaring arguments for ploting

    QString plot_command = " -f " + _PROFILE + " --sigma=1.0";
    QStringList plot_args = plot_command.split(" ");

    //checking if disk wind solution matches the configuration file
    if((DWIND_A != bp_a) || (DWIND_B != bp_b)){
        QMessageBox::warning(NULL,"Abort!", "You have to re-run the disk wind solution or change the parameters in the configuration file.\n");
        //cout<<"You have to re-run the disk wind solution or change the parameters in the configuration file.\n";
        QMessageBox::warning(NULL,"Abort!", BASECONFIG.toStdString().c_str());
        //cout<<"Configuration file: "<<BASECONFIG.toStdString()<<endl;
        //printConfigFile();
        printf("A = %e, B = %e\n", DWIND_A, DWIND_B);
        cout<<"Disk wind input file: "<<INBP.toStdString()<<endl;
        printf("A = %.2e, B = %e\n", bp_a, bp_b);

        return;
    }

    //running cv
    cout<<"Beginning CV!"<<endl;
    QFile::copy(BASECONFIG, WORKDIR + "cvmod/config");
    QString cv_command_line2;

    if (doSurface){
        if(tempType == 1){
            system("clear");
            cout<<"Creating Grid - Step 1/9... 0%"<<endl;
            QProcess CVProcess1;
            CVProcess1.start(CV, cv_args1);
            CVProcess1.waitForStarted(-1);
            int cv_process_1_pid = CVProcess1.pid();
            CVProcess1.waitForFinished(-1);

            //The option -T is used to make CV calculate the total densities in this phase, otherwise, it would only
            //calculate the total densities for the "only magnetosphere" case, when calculating the ionic equilibrium
            QString pid1Str = QString::number(cv_process_1_pid).rightJustified(5,'0');
            cv_command_line2 = " -J 1 -v 13 -T -G " + pid1Str + "." + CV_OUTPUT;
            //cout<<"CV command line 2 :"<<cv_command_line2.toStdString()<<endl;
        }else{
            cv_command_line2 = " -J 1 -v 13 ";
        }
        system("clear");
        cout<<"Creating surfaces file - 1/9... 6%"<<endl;

        QProcess CVProcess2;
        QStringList cv_args2 = cv_command_line2.split(" ");

        CVProcess2.start(CV, cv_args2, QProcess::Unbuffered | QProcess::ReadWrite);
        CVProcess2.waitForStarted(-1);
        int cv_process_2_pid = CVProcess2.pid();
        CVProcess2.waitForFinished(-1);



        //cout<<"CV 2 Pid: "<<cv_process_2_pid<<endl;
        QString pidStr = QString::number(cv_process_2_pid).rightJustified(5,'0');
        //cout<<"PidStr "<<pidStr.toStdString()<<endl;
        QString gridFileCVExit = pidStr + "." + CV_OUTPUT;
        //cout<<"gridFileCVExit: "<<gridFileCVExit.toStdString()<<endl;
        QFile::copy(gridFileCVExit,_NHTOTAL);
        QFile::remove(gridFileCVExit);
    }
    system("clear");
    cout<<"Calculating temperatures - Step 2/9... 11%";
    cout<<TEMPTYPE.toStdString() + "\n";
    QProcess TTEMP_PROCESS;
    TTEMP_PROCESS.start(TTEMP);
    TTEMP_PROCESS.waitForStarted(-1);
    TTEMP_PROCESS.write(TEMPINPUT.toStdString().c_str());
    TTEMP_PROCESS.waitForFinished(-1);
    QFile mmtemp(_TEMP_MAXMIN);
    if(!mmtemp.open(QFile::ReadOnly | QFile::Text) )
    {
        // It could not open
        QMessageBox::warning(NULL,"Abort", "Max and Min Temperatures File do not Exist!\n");
        return;
    }
    QTextStream mmtemp_allFile(&mmtemp);

    QString mmtemp_allString;
    mmtemp_allString.append(mmtemp_allFile.readAll());
    mmtemp_allString = mmtemp_allString.simplified();
    //qDebug()<<mmtemp_allString<<endl;
    double maxMagTemp = mmtemp_allString.section(" ", 3,3).toDouble();
    double minMagTemp = mmtemp_allString.section(" ",7,7).toDouble();
    double isoDiskWind = mmtemp_allString.section(" ",12,12).toDouble();
    //cout<<"Max Mag temp "<<maxMagTemp<<"Min Mag Temp "<<minMagTemp<<"Iso Disk Wind "<<isoDiskWind<<endl;
    mmtemp.close();

    QString dataBaseQuery = _QUERYBASE + " -s " + nameStar +" "+ QString::number(MSTAR) + " "+ QString::number(RSTAR) + " " + QString::number(starDiskInclination) + " "+ATMO_FILE + " " + QString::number(MAG_INNER_RADIUS)+ " "+QString::number(MAG_OUTER_RADIUS) +" " +QString::number(MASS_ACC_RATE)+ " " +QString::number(magnetoHeatingRate)+ " " +QString::number(minMagTemp)+ " " + QString::number(maxMagTemp) + " "+ QString::number(DWIND_INNER_RADIUS)+ " "+ QString::number(DWIND_OUTER_RADIUS) + " " +QString::number(diskwindHeatingRate)+" "+QString::number(diskwindMinTemperature) +" "+QString::number(DWIND_ZMAX)+ " " +QString::number(DWIND_A)+ " " +QString::number(DWIND_B)+ " " +QString::number(DWIND_LAUNCH_ANGLE)+ " " +QString::number(bp_lambda)+ " " +QString::number(bp_kappa)+ " " +QString::number(DWIND_DENSITY)+ " " +QString::number(M_LOSS_RATE)+ " " +QString::number(diskwindTemp)+ " " +QString::number(L_LEVEL)+ " " +QString::number(U_LEVEL)+ " " +QString::number(TRANS_FREQ)+ " " +_time_stamp;
    qDebug()<<dataBaseQuery<<endl;
    QProcess DBProcess;
    DBProcess.execute(dataBaseQuery);

    //system(dataBaseQuery.toStdString().c_str());
    QFile starExists(_EXISTSDB);
    if(!starExists.open(QFile::ReadOnly | QFile::Text) )
    {
        // It could not open
        QMessageBox::warning(NULL,"Abort", "Star Exists File do not open!\n");
        return;
    }
    QTextStream starExists_allFile(&starExists);
    QString starExists_allString;
    starExists_allString.append(starExists_allFile.readAll());
    starExists_allString = starExists_allString.simplified();
    QString conf = starExists_allString.section(" ", 0,0);
    QString timepath = starExists_allString.section(" ", 1,1);
    qDebug()<<"CONFFFF"<<conf<<endl<<"TIME PATH"<<timepath<<endl;
    QString result = "This star profile path is located at " + _PATHOUT + timepath + "_prof_Ha_"+ QString::number(IINC) + "_" + nameStar + ".pdf";
    if(conf.toInt() ==1){
         QMessageBox::warning(NULL,"The star is already calculated", "The stars parameters already exists on CV Data Base! Check the OUTPUT for it's line profile!\n");
         QMessageBox::warning(NULL,"Star profile path", result);
        return;
    }
    else{
        dataBaseQuery = _QUERYBASE +" -i "+ nameStar +" "+ QString::number(MSTAR) + " "+ QString::number(RSTAR) + " " + QString::number(starDiskInclination) + " "+ATMO_FILE + " " + QString::number(MAG_INNER_RADIUS)+ " "+QString::number(MAG_OUTER_RADIUS) +" " +QString::number(MASS_ACC_RATE)+ " " +QString::number(magnetoHeatingRate)+ " " +QString::number(minMagTemp)+ " " + QString::number(maxMagTemp) + " "+ QString::number(DWIND_INNER_RADIUS)+ " "+ QString::number(DWIND_OUTER_RADIUS) + " " +QString::number(diskwindHeatingRate)+" "+QString::number(diskwindMinTemperature) +" "+QString::number(DWIND_ZMAX)+ " " +QString::number(DWIND_A)+ " " +QString::number(DWIND_B)+ " " +QString::number(DWIND_LAUNCH_ANGLE)+ " " +QString::number(bp_lambda)+ " " +QString::number(bp_kappa)+ " " +QString::number(DWIND_DENSITY)+ " " +QString::number(M_LOSS_RATE)+ " " +QString::number(diskwindTemp)+ " " +QString::number(L_LEVEL)+ " " +QString::number(U_LEVEL)+ " " +QString::number(TRANS_FREQ)+ " " +_time_stamp;

    }

    QFile::remove(_EXISTSDB);


    cout<<"Temperature calculation complete! Using CV to calculate preliminary atomic populations...\n";

    QProcess CVProcess3;
    CVProcess3.start(CV, cv_args3);
    CVProcess3.waitForStarted(-1);
    int cv_process_3_pid = CVProcess3.pid();
    CVProcess3.waitForFinished(-1);

    QString pid3Str = QString::number(cv_process_3_pid).rightJustified(5,'0');
    QString ioneqlFileCVExit = pid3Str + "." + CV_OUTPUT;
    //cout<<"gridFileCVExit: "<<gridFileCVExit.toStdString()<<endl;
    QFile::copy(ioneqlFileCVExit,_IONEQL);
    QFile::remove(ioneqlFileCVExit);
    QFile::remove(_TEMPONLY);

    system("clear");
    cout<<"Calculating source functions - Step 3/9... 22%";
    QProcess CVProcess4;

    CVProcess4.start(CV,cv_args4);
    CVProcess4.waitForStarted(-1);
    int cv_process_4_pid = CVProcess4.pid();
    CVProcess4.waitForFinished(-1);
    QTime CV_END_TIME = QTime::currentTime();
    QString pid4Str = QString::number(cv_process_4_pid).rightJustified(5,'0');
    QString sourceFileCVExit = pid4Str + "." + CV_OUTPUT;
    //cout<<"gridFileCVExit: "<<gridFileCVExit.toStdString()<<endl;
    QFile::copy(sourceFileCVExit,_SOURCE);
    QFile::remove(sourceFileCVExit);
    QFile::remove(_IONEQL);
    cout<<"CV is done!";
    int difference = _time_now.time().secsTo(CV_END_TIME);
    cout<<"Running time: "<<difference<<"s"<<endl;

    QFile testGrid(_NHTOTAL);
    if(!testGrid.exists()){
        QMessageBox::warning(NULL,"Abort", "There's no grid file already made, you have to select the doSurface option!\n");
        return;
    }

    system("clear");
    cout<<"Recalculating atomic populations - Step 3/9... 33%";
    QProcess HydroProcess;
    HydroProcess.start(HYDRO);
    HydroProcess.waitForStarted(-1);
    HydroProcess.write(HYDROINPUT.toStdString().c_str());
    HydroProcess.waitForFinished(-1);
    QTime HYDRO_END_TIME = QTime::currentTime();
    cout<<"HYDRO is done! ";
    difference = _time_now.time().secsTo(HYDRO_END_TIME);
    cout<<"Running time: "<<difference<<"s"<<endl;

    system("clear");
    cout<<"Reformating the Grid for Flux - Step 5/9... 55%";

    QProcess GridoutProcess;
    GridoutProcess.start(GRIDOUT);
    GridoutProcess.waitForStarted(-1);
    int gridout_process_pid = GridoutProcess.pid();
    GridoutProcess.write(GRIDOUTINPUT.toStdString().c_str());
    GridoutProcess.waitForFinished(-1);
    QTime GRIDOUT_END_TIME = QTime::currentTime();
    QString pidGridoutStr = QString::number(gridout_process_pid).rightJustified(5,'0');
    QString gridoutFileExit = pidGridoutStr + "." + CV_OUTPUT;
    QFile::copy(gridoutFileExit,_TEMP);
    QFile::remove(gridoutFileExit);
    cout<<"GRIDOUT is done! ";
    difference = _time_now.time().secsTo(GRIDOUT_END_TIME);
    cout<<"Running time: "<<difference<<"s"<<endl;

    system("clear");
    cout<<"Resampling the grid - Step 6/9... 66%";
    QProcess SamplingProcess;
    SamplingProcess.start(SAMPLING,sampling_args);
    SamplingProcess.waitForFinished(-1);
    QTime SAMPLING_END_TIME = QTime::currentTime();
    QString samplingFileExit = _TEMP+"_gridsize.dat";
    QFile::copy(samplingFileExit,_GRIDSIZE);
    QFile::remove(samplingFileExit);
    cout<<"Resampling process is done! ";
    difference = _time_now.time().secsTo(SAMPLING_END_TIME);
    cout<<"Running time: "<<difference<<"s"<<endl;

    system("clear");
    cout<<"Fixing resampled grid - Step 7/9... 77%";

    QProcess FixProcess;
    FixProcess.start(FIX);
    FixProcess.waitForStarted(-1);
    FixProcess.write(FIXINPUT.toStdString().c_str());
    FixProcess.waitForFinished(-1);
    QTime FIX_END_TIME = QTime::currentTime();
    cout<<"Fixing grid is done! ";
    difference = _time_now.time().secsTo(FIX_END_TIME);
    cout<<"Running time: "<<difference<<"s"<<endl;

    system("clear");
    cout<<"Calculating line profile - Step 8/9... 88%";

    QProcess FluxProcess;
    FluxProcess.start(FLUX);
    FluxProcess.waitForStarted(-1);
    FluxProcess.write(FLUXINPUT.toStdString().c_str());
    FluxProcess.waitForFinished(-1);
    QTime FLUX_END_TIME = QTime::currentTime();
    QFile::remove(_TEMP);
    QFile::remove(_FIXIN);
    QFile::remove(_TEMP_MAXMIN);
    cout<<"Flux is done! ";
    difference = _time_now.time().secsTo(FLUX_END_TIME);
    cout<<"Running time: "<<difference<<endl;

    QFile grd_size(_GRIDSIZE);
    if(!grd_size.open(QFile::ReadOnly | QFile::Text) )
    {
        // It could not open
        QMessageBox::warning(NULL,"Abort", "Grid File failed to open!\n");
        return;
    }
    QTextStream gridSize_allFile(&grd_size);

    QString grdSize_allString;
    grdSize_allString.append(gridSize_allFile.readAll());
    grdSize_allString = grdSize_allString.simplified();

    //double maxMagTemp = mmtemp_allString.section(" ", 3,3).toDouble();
    //double minMagTemp = mmtemp_allString.section(" ",7,7).toDouble();
    //double isoDiskWind = mmtemp_allString.section(" ",12,12).toDouble();

    QFile::remove(_GRIDSIZE);

    if(!doMap){
        cout<<"Intensity maps data erased!"<<endl;
        QFile::remove(_INTENSMAP);
    }
    system("clear");
    cout<<"Fixing resampled grid - Step 9/9... 100%";

    QFile outFile(_PARAM);
    outFile.open(QFile::WriteOnly);
    QTextStream param(&outFile);

    param<<"! "<<nameStar<<"\n \n"<<
           "! stellar mass: "<<MSTAR<<
           ",stellar radius: "<<RSTAR<<"\n"<<
           "! system inclination: "<<starDiskInclination<<"\n";

    if(USE_ATMOSPHERE == 1){
        param<<"! Using atmospheric model: "<<ATMO_FILE<<"\n\n";
    }else{
        param<<"! Using star as a blackbody. Photospheric temperature: "<<PHOT_TEMP<<"\n\n";
    }

    param<<"! "<<TEMPTYPE<<"\n \n";
    if(tempType == 1){
        param<<"! Magnetosphere \n";
        param<<"! inner radius: "<<MAG_INNER_RADIUS<<", outer radius: "<<MAG_OUTER_RADIUS<<endl;
        param<<"! mass accretion rate: "<<MASS_ACC_RATE<<endl;
        param<<"! heating rate: "<< magnetoHeatingRate<<endl;
        param<<"! minimum temperature: "<<minMagTemp<<", maximum temperature: "<<maxMagTemp<<endl<<endl;
    }else if(tempType == 2){
        param<<"! Disk wind "<<endl;
        param<<"! inner radius: "<<DWIND_INNER_RADIUS<<", outer radius: "<<DWIND_OUTER_RADIUS<<endl;
        param<<"! maximum height: "<<DWIND_ZMAX<<endl;
        param<<"! Coeficients\t A: "<<DWIND_A<<", B: "<<DWIND_B<<endl;
        param<<"! Disk wind lauching angle: "<<DWIND_LAUNCH_ANGLE<<" degrees"<<endl;
        param<<"! Lambda: "<<bp_lambda<<", Kappa: "<<bp_kappa<<endl;
        param<<"! fiducial density: "<<DWIND_DENSITY<<" g cm^-3"<<endl;
        param<<"! mass loss rate: "<<M_LOSS_RATE<<" Msun yr^-1"<<endl;
        param<<"! heating rate: "<<diskwindHeatingRate<<endl;
        param<<"! minimum temperature: "<< minMagTemp<<", maximum temperature: "<< maxMagTemp<<endl<<endl;
    }else if(tempType == 3){
        param<<"! Disk wind "<<endl;
        param<<"! inner radius: "<<DWIND_INNER_RADIUS<<", outer radius: "<<DWIND_OUTER_RADIUS<<endl;
        param<<"! maximum height: "<<DWIND_ZMAX<<endl;
        param<<"! Coeficients\t A: "<<DWIND_A<<", B: "<<DWIND_B<<endl;
        param<<"! Disk wind lauching angle: "<<DWIND_LAUNCH_ANGLE<<" degrees"<<endl;
        param<<"! Lambda: "<<bp_lambda<<", Kappa: "<<bp_kappa<<endl;
        param<<"! fiducial density: "<<DWIND_DENSITY<<" g cm^-3"<<endl;
        param<<"! mass loss rate: "<<M_LOSS_RATE<<" Msun yr^-1"<<endl;
        param<<"! heating rate: "<<diskwindHeatingRate<<endl;
        param<<"! lowest possible disk wind temperature: "<<diskwindMinTemperature<<endl;
        param<<"! minimum temperature: "<<minMagTemp<<", maximum temperature: "<<maxMagTemp<<endl<<endl;
    }else if(tempType == 4){
        param<<"! Disk wind "<<endl;
        param<<"! inner radius: "<<DWIND_INNER_RADIUS<<", outer radius: "<<DWIND_OUTER_RADIUS<<endl;
        param<<"! maximum height: "<<DWIND_ZMAX<<endl;
        param<<"! Coeficients\t A: "<<DWIND_A<<", B: "<<DWIND_B<<endl;
        param<<"! Disk wind lauching angle: "<<DWIND_LAUNCH_ANGLE<<" degrees"<<endl;
        param<<"! Lambda: "<<bp_lambda<<", Kappa: "<<bp_kappa<<endl;
        param<<"! fiducial density: "<<DWIND_DENSITY<<" g cm^-3"<<endl;
        param<<"! mass loss rate: "<<M_LOSS_RATE<<" Msun yr^-1"<<endl;
        param<<"! isothermal disk wind temperature: "<< diskwindTemp<<endl<<endl;
    }else if(tempType == 5){
        param<<"! Magnetosphere"<<endl;
        param<<"! inner radius: "<<MAG_INNER_RADIUS<<", outer radius: "<<MAG_OUTER_RADIUS<<endl;
        param<<"! mass accretion rate: "<<MASS_ACC_RATE<<endl;
        param<<"! heating rate: "<< magnetoHeatingRate<<endl;
        param<<"! minimum temperature: "<<minMagTemp<<", maximum temperature: "<<maxMagTemp<<endl;

        param<<"! Disk wind "<<endl;
        param<<"! inner radius: "<<DWIND_INNER_RADIUS<<", outer radius: "<<DWIND_OUTER_RADIUS<<endl;
        param<<"! maximum height: "<<DWIND_ZMAX<<endl;
        param<<"! Coeficients\t A: "<<DWIND_A<<", B: "<<DWIND_B<<endl;
        param<<"! Disk wind lauching angle: "<<DWIND_LAUNCH_ANGLE<<" degrees"<<endl;
        param<<"! Lambda: "<<bp_lambda<<", Kappa: "<<bp_kappa<<endl;
        param<<"! fiducial density: "<<DWIND_DENSITY<<" g cm^-3"<<endl;
        param<<"! mass loss rate: "<<M_LOSS_RATE<<" Msun yr^-1"<<endl;
        param<<"! heating rate: "<<diskwindHeatingRate<<endl;
        param<<"! minimum temperature: "<<minMagTemp<<", maximum temperature: "<<maxMagTemp<<endl<<endl;
    }else if(tempType == 6){
        param<<"! Magnetosphere"<<endl;
        param<<"! inner radius: "<<MAG_INNER_RADIUS<<", outer radius: "<<MAG_OUTER_RADIUS<<endl;
        param<<"! mass accretion rate: "<<MASS_ACC_RATE<<endl;
        param<<"! heating rate: "<< magnetoHeatingRate<<endl;
        param<<"! minimum temperature: "<<minMagTemp<<", maximum temperature: "<<maxMagTemp<<endl;

        param<<"! Disk wind "<<endl;
        param<<"! inner radius: "<<DWIND_INNER_RADIUS<<", outer radius: "<<DWIND_OUTER_RADIUS<<endl;
        param<<"! maximum height: "<<DWIND_ZMAX<<endl;
        param<<"! Coeficients\t A: "<<DWIND_A<<", B: "<<DWIND_B<<endl;
        param<<"! Disk wind lauching angle: "<<DWIND_LAUNCH_ANGLE<<" degrees"<<endl;
        param<<"! Lambda: "<<bp_lambda<<", Kappa: "<<bp_kappa<<endl;
        param<<"! fiducial density: "<<DWIND_DENSITY<<" g cm^-3"<<endl;
        param<<"! mass loss rate: "<<M_LOSS_RATE<<" Msun yr^-1"<<endl;
        param<<"! heating rate: "<<diskwindHeatingRate<<endl;
        param<<"! lowest possible disk wind temperature: "<<diskwindMinTemperature<<endl;
        param<<"! minimum temperature: "<<minMagTemp<<", maximum temperature: "<<maxMagTemp<<endl<<endl;
    }else if(tempType == 7){
        param<<"! Magnetosphere"<<endl;
        param<<"! inner radius: "<<MAG_INNER_RADIUS<<", outer radius: "<<MAG_OUTER_RADIUS<<endl;
        param<<"! mass accretion rate: "<<MASS_ACC_RATE<<endl;
        param<<"! heating rate: "<< magnetoHeatingRate<<endl;
        param<<"! minimum temperature: "<<minMagTemp<<", maximum temperature: "<<maxMagTemp<<endl;

        param<<"! Disk wind "<<endl;
        param<<"! inner radius: "<<DWIND_INNER_RADIUS<<", outer radius: "<<DWIND_OUTER_RADIUS<<endl;
        param<<"! maximum height: "<<DWIND_ZMAX<<endl;
        param<<"! Coeficients\t A: "<<DWIND_A<<", B: "<<DWIND_B<<endl;
        param<<"! Disk wind lauching angle: "<<DWIND_LAUNCH_ANGLE<<" degrees"<<endl;
        param<<"! Lambda: "<<bp_lambda<<", Kappa: "<<bp_kappa<<endl;
        param<<"! fiducial density: "<<DWIND_DENSITY<<" g cm^-3"<<endl;
        param<<"! mass loss rate: "<<M_LOSS_RATE<<" Msun yr^-1"<<endl;
        param<<"! isothermal disk wind temperature: "<< diskwindTemp<<endl<<endl;
    }

    param<<"! Hydrogen line profile"<<endl<<endl;
    param<<"! transistion lower level: "<< L_LEVEL<<", upper level: "<<U_LEVEL<<endl;
    param<<"! central line frequency: "<<TRANS_FREQ<<endl<<endl;
    param<<"! Grid size: "<<grdSize_allString.section(" ", 0,0)<<" x "<<grdSize_allString.section(" ",1,1)<<endl;

    grd_size.close();
    outFile.flush();
    outFile.close();

    DBProcess.execute(dataBaseQuery);//Inserting star on DB

    //Printing profile parameters
    cout<<"\n \n Line profile parameters \n"<<endl;
    QFile param_file(_PARAM);
    param_file.open(QFile::ReadOnly);
    QTextStream parameters(&param_file);
    QString parame = parameters.readAll();
    cout<<parame.toStdString()<<endl;
    cout<<endl<<endl;
    param_file.close();


    QMessageBox::information(NULL,"Physical Parameters", parame.toStdString().c_str());
    //Ploting profile

    QProcess CompletePlot;
    CompletePlot.execute(PLOT, plot_args);

}

void CVInputData::on_pushButton_2_clicked() {
    if ((getOutFileName() == "") || (getOutFileName()=="newconfig.STAR_TYPE") || (ui->lineEdit_82->text()=="")) {
        if(ui->lineEdit_82->text()==""){
            QMessageBox::warning(this, "Error!", "Set the Temperature Type!");
        }else{
            QMessageBox::warning(this, "Error!", "Set the exit file name!");
        }
    }else{
        writeParameters();
        run();
        //QMessageBox::information(this, "CV Running!", "CV Running in background...");
        close();
    }

}

void CVInputData::on_lineEdit_4_editingFinished() {
    setSpecialJ(ui->lineEdit_4->text());
}

void CVInputData::on_pushButton_3_clicked() {
    QMessageBox::information(this, "Help!", "The 'i' index of the source grid point where AUXVERBOSE level will be used. (-1 => don't use)");
}

void CVInputData::on_pushButton_4_clicked() {
    QMessageBox::information(this, "Help!", "The 'j' index of the source grid point where AUXVERBOSE level will be used. (-1 => don't use)");
}

void CVInputData::on_pushButton_5_clicked() {
    QMessageBox::information(this, "Help!", "Put the number of a code listed below to select a cv model.\nVelocity law also dictates the geometry: \n\n0:RADIAL\n1:MAGNETO\n2:INFALL\n3:HUMMER\n4:ROTMAGNETO\n5:MAGNETOTABLE\n6:DISKWIND\n7:MAGNETO + DISKWIND");
}

void CVInputData::on_lineEdit_7_editingFinished() {
    setAtmosphereType(ui->lineEdit_7->text());
}

void CVInputData::on_pushButton_6_clicked() {
    QMessageBox::information(this, "Help!", "0:Blackbody\n1:Atmosphere");
}

void CVInputData::on_lineEdit_8_editingFinished() {
    setJobType(ui->lineEdit_8->text());
}

void CVInputData::on_pushButton_7_clicked() {
    QMessageBox::information(this, "Help!", "Indicate what phase of a cv job you want to run by selecting one of the codes listed in the accompanying comment.\n\n 0:ignore\n 1:surface\n 2:sourcen\n 3:profile\n 4:ioneql\n 5:makegrid");
}

void CVInputData::on_lineEdit_9_editingFinished() {
    setUseGridFile(ui->lineEdit_9->text());
}

void CVInputData::on_pushButton_8_clicked() {
    QMessageBox::information(this, "Help!", "Use the information in GRID_FILENAME for densities and temperatures over the grid.");

}

void CVInputData::on_lineEdit_10_editingFinished() {
    setUseTemperaturesOnly(ui->lineEdit_10->text());
}

void CVInputData::on_pushButton_9_clicked() {
    QMessageBox::information(this, "Help!", "Use the information in GRID_FILENAME only for temperatures over the grid.");
}

void CVInputData::on_lineEdit_11_editingFinished() {
    setGridFilename(ui->lineEdit_11->text());
}

void CVInputData::on_pushButton_10_clicked() {
    QMessageBox::information(this, "Help!", "A file of densities and temperatures over the grid.\n\nex:grid.dat");

}

void CVInputData::on_pushButton_11_clicked() {
    QMessageBox::information(this, "Help!", "A file of binary surface information.\n\nex:surfaces.ABAur");
}

void CVInputData::on_actionExit_triggered() {
    close();
}

void CVInputData::on_actionInstructions_triggered() {
    QMessageBox::information(this, "Instructions", "Instructions:\n\nDon't use '#' or '=' as part of a label name.\nExcept where numerically keyed selections are in use, '0' (zero) means no, and '1' (one) means yes.\n\nThis application makes a parameters file with data here inserted.\nDon't forget push button 'Create a Parameters File' before get out.\nIf you don't know what kind of parameters the lable need, click on the button 'i'.\nIf no changes be made, the pattern parameters will be writed.");
}

void CVInputData::on_lineEdit_13_editingFinished() {
    setVelocityFilename(ui->lineEdit_13->text());
}

void CVInputData::on_pushButton_13_clicked() {
    QMessageBox::information(this, "Help!", "A file of velocity data, currently used in MAGNETOTABLE and DISKWIND\n\nex:diskwindxcv_ABAur");
}

void CVInputData::on_lineEdit_14_editingFinished() {
    setProfVelFilename(ui->lineEdit_14->text());
}

void CVInputData::on_pushButton_14_clicked() {
    QMessageBox::information(this, "Help!", "A file of a list of velocities at which line profile intensities are to be found.\n\nex:profveltable");
}

void CVInputData::on_lineEdit_15_editingFinished() {
    setAtmosphereFilename(ui->lineEdit_15->text());
}

void CVInputData::on_pushButton_15_clicked() {
    QMessageBox::information(this, "Help!", "A file containing the frequencies and fluxes emitted from the star.\n\nex:ABAur_Atmo.dat");
}

void CVInputData::on_ExitFileLine_editingFinished() {
    setOutFileName(ui->ExitFileLine->text());
}

void CVInputData::on_VerboseButton_clicked() {
    QMessageBox::information(this, "Help!", "Put the number of a code listed below to control verbose output.\n\n0:NONE\n1:SURFACE\n2:DIAG\n3:FIELD\n4:VELTABLE\n5:INT\n6:JBAR\n7:GRAD\n8:SOURCE\n9:PROFILE\n10:SOURCESURFACE\n11:GRID\n12:CROSSING\n13:MONITOR");
    QMessageBox::warning(this, "Warning", "Using 2:DIAG for a normally dimensioned job can easily fill a disk.");
}

void CVInputData::on_AuxVerboseButton_clicked() {
    QMessageBox::information(this, "Help!", "Put the number of a code listed below to control verbose output.\n\n0:NONE\n1:SURFACE\n2:DIAG\n3:FIELD\n4:VELTABLE\n5:INT\n6:JBAR\n7:GRAD\n8:SOURCE\n9:PROFILE\n10:SOURCESURFACE\n11:GRID\n12:CROSSING\n13:MONITOR");
    QMessageBox::warning(this, "Warning", "Using 2:DIAG for a normally dimensioned job can easily fill a disk.");
}

void CVInputData::on_lineEdit_editingFinished() {
    setVerbose(ui->lineEdit->text());
}

void CVInputData::on_lineEdit_2_editingFinished() {
    setAuxverbose(ui->lineEdit_2->text());
}

void CVInputData::on_lineEdit_3_editingFinished() {
    setSpecialI(ui->lineEdit_3->text());
}

void CVInputData::on_lineEdit_5_editingFinished() {
    setVelocityLaw(ui->lineEdit_5->text());
}

void CVInputData::on_lineEdit_6_editingFinished() {
    setStellarRadInRsun(ui->lineEdit_6->text());
}

void CVInputData::on_pushButton_clicked() {
    QMessageBox::information(this, "Help!", "Stellar radius in Rsun.");
}

void CVInputData::on_lineEdit_16_editingFinished() {
    setStellarMassInMsun(ui->lineEdit_16->text());
}

void CVInputData::on_pushButton_12_clicked() {
    QMessageBox::information(this, "Help!", "Stellar mass in Msun.");
}

void CVInputData::on_lineEdit_17_editingFinished() {
    setMaxRadius(ui->lineEdit_17->text());
}

void CVInputData::on_pushButton_16_clicked() {
    QMessageBox::information(this, "Help!", "All computation occurs within this number of stellar radii, unless overriden by DISKWIND outer corner, or OUTER_R0.");
}

void CVInputData::on_lineEdit_18_editingFinished() {
    setTempStar(ui->lineEdit_18->text());
}

void CVInputData::on_pushButton_17_clicked() {
    QMessageBox::information(this, "Help!", "Temperature of stellar photosphere.");
}

void CVInputData::on_lineEdit_19_editingFinished() {
    setTempRing(ui->lineEdit_19->text());
}

void CVInputData::on_pushButton_18_clicked() {
    QMessageBox::information(this, "Help!", "Only consulted in magnetosphere cases.");
}

void CVInputData::on_lineEdit_20_editingFinished() {
    setRadiationTemp(ui->lineEdit_20->text());
}

void CVInputData::on_pushButton_19_clicked() {
    QMessageBox::information(this, "Help!", "For IONEQL.");
}

void CVInputData::on_lineEdit_21_editingFinished() {
    setTempGas(ui->lineEdit_21->text());
}

void CVInputData::on_pushButton_20_clicked() {
    QMessageBox::information(this, "Help!", "Ignored if USE_GRID_FILE or USE_TEMPERATURES_ONLY is yes.");
}

void CVInputData::on_lineEdit_22_editingFinished() {
    setFixedEpsilon(ui->lineEdit_22->text());
}

void CVInputData::on_pushButton_21_clicked() {
    QMessageBox::information(this, "Help!", "Set this to negative to disable.");
}

void CVInputData::on_lineEdit_23_editingFinished() {
    setUseAtomFile(ui->lineEdit_23->text());
}

void CVInputData::on_pushButton_22_clicked() {
    QMessageBox::information(this, "Help!", "1 means yes, 0 means no.");
}

void CVInputData::on_lineEdit_24_editingFinished() {
    setDoMulti(ui->lineEdit_24->text());
}

void CVInputData::on_pushButton_23_clicked() {
    QMessageBox::information(this, "Help!", "1 means yes, 0 means no.  Multi means derive source from n(lower), n(upper).");
}

void CVInputData::on_lineEdit_25_editingFinished() {
    setElement(ui->lineEdit_25->text());
}

void CVInputData::on_pushButton_24_clicked() {
    QMessageBox::information(this, "Help!", "Use the atomic number.");
}

void CVInputData::on_lineEdit_26_editingFinished() {
    setAtomFilename(ui->lineEdit_26->text());
}

void CVInputData::on_pushButton_25_clicked() {
    QMessageBox::information(this, "Help!", "The name of the file containing atomic parameters.");
}

void CVInputData::on_lineEdit_27_editingFinished() {
    setLowerLevel(ui->lineEdit_27->text());
}

void CVInputData::on_pushButton_26_clicked() {
    QMessageBox::information(this, "Help!", "For H");
}

void CVInputData::on_lineEdit_28_editingFinished() {
    setUpperLevel(ui->lineEdit_28->text());
}

void CVInputData::on_pushButton_27_clicked() {
    QMessageBox::information(this, "Help!", "For H");
}

void CVInputData::on_lineEdit_29_editingFinished() {
    setAbundance(ui->lineEdit_29->text());
}

void CVInputData::on_pushButton_28_clicked() {
    QMessageBox::information(this, "Help!", "Set this fudge factor to one if using atom file.");
}

void CVInputData::on_lineEdit_30_editingFinished() {
    setOscillator(ui->lineEdit_30->text());
}

void CVInputData::on_lineEdit_31_editingFinished() {
    setCUpperlevel(ui->lineEdit_31->text());
}

void CVInputData::on_lineEdit_32_editingFinished() {
    setAUpperlevel(ui->lineEdit_32->text());
}

void CVInputData::on_lineEdit_33_editingFinished() {
    setFrequency(ui->lineEdit_33->text());
}

void CVInputData::on_pushButton_29_clicked() {
    QMessageBox::information(this, "Help!", "If zero, determine from WAVELENGTH.");
}

void CVInputData::on_lineEdit_34_editingFinished() {
    setWavelenght(ui->lineEdit_34->text());
}

void CVInputData::on_pushButton_30_clicked() {
    QMessageBox::information(this, "Help!", "In cm");
}

void CVInputData::on_lineEdit_35_editingFinished() {
    setLineDepth(ui->lineEdit_35->text());
}

void CVInputData::on_lineEdit_36_editingFinished() {
    setLineDopplerWidth(ui->lineEdit_36->text());
}

void CVInputData::on_pushButton_31_clicked() {
    QMessageBox::information(this, "Help!", "In km/s");
}

void CVInputData::on_pushButton_32_clicked() {
    QMessageBox::information(this, "Help!", "correction=1-LINE_DEPTH*((1-LINE_WING)*exp(-x*x)+LINE_WING/((1+x)**2))\nx=v/LINE_DOPPLER_WIDTH, v=velocity from line center.");
}

void CVInputData::on_lineEdit_37_editingFinished() {
    setLineWing(ui->lineEdit_37->text());
}

void CVInputData::on_lineEdit_38_editingFinished() {
    setSuppressRotation(ui->lineEdit_38->text());
}

void CVInputData::on_lineEdit_39_editingFinished() {
    setDoHotspot(ui->lineEdit_39->text());
}

void CVInputData::on_lineEdit_40_editingFinished() {
    setHotspotphi1(ui->lineEdit_40->text());
}

void CVInputData::on_pushButton_33_clicked() {
    QMessageBox::information(this, "Help!", "In degrees");
}

void CVInputData::on_lineEdit_41_editingFinished() {
    setHotspotphi2(ui->lineEdit_41->text());
}

void CVInputData::on_pushButton_34_clicked() {
    QMessageBox::information(this, "Help!", "In degrees");
}

void CVInputData::on_lineEdit_42_editingFinished() {
    setDiskwindInnerXo(ui->lineEdit_42->text());
}

void CVInputData::on_lineEdit_43_editingFinished() {
    setDiskwindOuterXo(ui->lineEdit_43->text());
}

void CVInputData::on_lineEdit_44_editingFinished() {
    setDiskwindZHeight(ui->lineEdit_44->text());
}

void CVInputData::on_lineEdit_45_editingFinished() {
    setDiskwindA(ui->lineEdit_45->text());
}

void CVInputData::on_lineEdit_46_editingFinished() {
    setDiskwindB(ui->lineEdit_46->text());
}

void CVInputData::on_lineEdit_47_editingFinished() {
    setDiskwindRho0(ui->lineEdit_47->text());
}

void CVInputData::on_lineEdit_48_editingFinished() {
    setDiskwindTdmax(ui->lineEdit_48->text());
}

void CVInputData::on_lineEdit_49_editingFinished() {
    setDensityFactor(ui->lineEdit_49->text());
}

void CVInputData::on_pushButton_35_clicked() {
    QMessageBox::information(this, "Help!", "Densities in MAGNETOTABLE velocity table get multiplied by this.");
}

void CVInputData::on_lineEdit_50_editingFinished() {
    setMassFlow(ui->lineEdit_50->text());
}

void CVInputData::on_pushButton_36_clicked() {
    QMessageBox::information(this, "Help!", "gm/s, this is the handle on densConst.");
}

void CVInputData::on_lineEdit_51_editingFinished() {
    setInnerR0(ui->lineEdit_51->text());
}

void CVInputData::on_pushButton_37_clicked() {
    QMessageBox::information(this, "Help!", "radius where inner field line intersects disk plane.");
}

void CVInputData::on_lineEdit_52_editingFinished() {
    setOuterR0(ui->lineEdit_52->text());
}

void CVInputData::on_pushButton_38_clicked() {
    QMessageBox::information(this, "Help!", "radius where outer field line intersects disk plane.");
}

void CVInputData::on_lineEdit_53_editingFinished() {
    setBeq(ui->lineEdit_53->text());
}

void CVInputData::on_pushButton_39_clicked() {
    QMessageBox::information(this, "Help!", "equatorial stellar magnetic field in Gauss.");
}

void CVInputData::on_lineEdit_54_editingFinished() {
    setPolVelInner(ui->lineEdit_54->text());
}

void CVInputData::on_pushButton_40_clicked() {
    QMessageBox::information(this, "Help!", "initial poloidal velocity on the inner field line in units of (G*Mstar/Rstar).");
}

void CVInputData::on_lineEdit_55_editingFinished() {
    setOmegask(ui->lineEdit_55->text());
}

void CVInputData::on_pushButton_41_clicked() {
    QMessageBox::information(this, "Help!", "ratio of omega(star) to omega(Keplerian).");
}

void CVInputData::on_lineEdit_56_editingFinished() {
    setXlin(ui->lineEdit_56->text());
}

void CVInputData::on_pushButton_42_clicked() {
    QMessageBox::information(this, "Help!", "specific angular momentum for the inner field line in units of (G*Mstar/Rstar)^(1/2).");
}

void CVInputData::on_lineEdit_57_editingFinished() {
    setRhTau0(ui->lineEdit_57->text());
}

void CVInputData::on_lineEdit_58_editingFinished() {
    setMaxIteration(ui->lineEdit_58->text());
}

void CVInputData::on_pushButton_43_clicked() {
    QMessageBox::information(this, "Help!", "See cvdim.h for maximum allowable dimensions.");
}

void CVInputData::on_lineEdit_59_editingFinished() {
    setSourceX(ui->lineEdit_59->text());
}

void CVInputData::on_lineEdit_60_editingFinished() {
    setSourceZ(ui->lineEdit_60->text());
}

void CVInputData::on_lineEdit_61_editingFinished() {
    setSourcePhi(ui->lineEdit_61->text());
}

void CVInputData::on_lineEdit_62_editingFinished() {
    setSourceTheta(ui->lineEdit_62->text());
}

void CVInputData::on_lineEdit_63_editingFinished() {
    setSourceStep(ui->lineEdit_63->text());
}

void CVInputData::on_pushButton_44_clicked() {
    QMessageBox::information(this, "Help!", "This parameter is overridden in magnetosphere case.");
}

void CVInputData::on_lineEdit_64_editingFinished() {
    setSourceThetastarFrac(ui->lineEdit_64->text());
}

void CVInputData::on_pushButton_45_clicked() {
    QMessageBox::information(this, "Help!", "Number of rays on star is NSOURCE_THETA/SOURCE_THETASTAR_FRAC.");
}

void CVInputData::on_lineEdit_65_editingFinished() {
    setProfVelFactor(ui->lineEdit_65->text());
}

void CVInputData::on_pushButton_46_clicked() {
    QMessageBox::information(this, "Help!", "If negative, scale values in PROF_VEL_TABLE by max velocity");
}

void CVInputData::on_lineEdit_66_editingFinished() {
    setNprofileVelocity(ui->lineEdit_66->text());
}

void CVInputData::on_lineEdit_67_editingFinished() {
    setNprofileAngle(ui->lineEdit_67->text());
}

void CVInputData::on_lineEdit_68_editingFinished() {
    setNprofileRadii(ui->lineEdit_68->text());
}

void CVInputData::on_pushButton_47_clicked() {
    QMessageBox::information(this, "Help!", "This is the total number of radii, including NPROFILE_STAR_RADII.");
}

void CVInputData::on_lineEdit_69_editingFinished() {
    setNprofileStarRadii(ui->lineEdit_69->text());
}

void CVInputData::on_lineEdit_70_editingFinished() {
    setNprofileStep(ui->lineEdit_70->text());
}

void CVInputData::on_pushButton_48_clicked() {
    QMessageBox::information(this, "Help!", "This parameter is overridden in magnetosphere case.");
}

void CVInputData::on_lineEdit_71_editingFinished() {
    setFirstVelocity(ui->lineEdit_71->text());
}

void CVInputData::on_pushButton_49_clicked() {
    QMessageBox::information(this, "Help!", "km/s");
}

void CVInputData::on_lineEdit_72_editingFinished() {
    setLastVelocity(ui->lineEdit_72->text());
}

void CVInputData::on_lineEdit_73_editingFinished() {
    setInclination(ui->lineEdit_73->text());
}

void CVInputData::on_pushButton_50_clicked() {
    QMessageBox::information(this, "Help!", "90o is equator-on, 0o is pole-on.  Ordinarily control using -i command line.");
}

void CVInputData::on_pushButton_51_clicked() {
    QMessageBox::information(this, "Help!", "Can use these with JOB_TYPE 0, ordinarily JOB_TYPE!=0 overrides these.");
}

void CVInputData::on_lineEdit_74_editingFinished() {
    setUsedSavedSurfaces(ui->lineEdit_74->text());
}

void CVInputData::on_pushButton_52_clicked() {
    QMessageBox::information(this, "Help!", "0 means don't use SURFACES_FILENAME as a surface file, 1 means do.");
}

void CVInputData::on_lineEdit_75_editingFinished() {
    setSaveSurfaces(ui->lineEdit_75->text());
}

void CVInputData::on_lineEdit_76_editingFinished() {
    setUseSavedSource(ui->lineEdit_76->text());
}

void CVInputData::on_pushButton_53_clicked() {
    QMessageBox::information(this, "Help!", "0 means don't use SOURCE_NAME as source function, 1 means do.");
}

void CVInputData::on_lineEdit_77_editingFinished() {
    setSaveSource(ui->lineEdit_77->text());
}

void CVInputData::on_pushButton_54_clicked() {
    QMessageBox::information(this, "Help!", "0 means don't save source function to SOURCE_NAME (overwrites), 1 means do.");
}

void CVInputData::on_lineEdit_78_editingFinished() {
    setDoProfile(ui->lineEdit_78->text());
}

void CVInputData::on_lineEdit_79_editingFinished() {
    setDoIoneql(ui->lineEdit_79->text());
}

void CVInputData::on_pushButton_55_clicked()
{
    QMessageBox::information(this, "Help!", "Define the system inclination (default = 55 degrees).");
}

void CVInputData::on_pushButton_56_clicked()
{
    QMessageBox::information(this, "Help!", "These parameters will not be writed in the newconfig file, it is just for the CV Script when running CV!");
}

void CVInputData::on_lineEdit_80_editingFinished()
{
    setStarDiskInclination(ui->lineEdit_80->text().toFloat());
}

void CVInputData::on_lineEdit_81_editingFinished()
{
    setNameStar(ui->lineEdit_81->text());
    setOutFileName(FILEEXITADRESS + getNameStar());
    ui->ExitFileLine->clear();
    ui->ExitFileLine->insert(FILEEXITADRESS + getNameStar());
}

void CVInputData::on_pushButton_57_clicked()
{
    QMessageBox::information(this, "Help!", "This is the name of the star you want to model");
}

void CVInputData::on_pushButton_58_clicked()
{
    QMessageBox::information(this, "Help!", "Calculate the surface file");
}

void CVInputData::on_lineEdit_82_editingFinished()
{
    if(ui->lineEdit_82->text().toInt()>0 && ui->lineEdit_82->text().toInt()<=7){
        setTempType(ui->lineEdit_82->text().toInt());
        //cout<<"Tem ptype alterado:"<<getTempType();

    }else{
        QMessageBox::warning(this, "Warning!", "This is not a possible value!");
    }
}

void CVInputData::on_pushButton_59_clicked()
{
    QMessageBox::information(this, "Help!", "An integer that defines the temperatures type:\n1: Magnetosphere only\n2: Disk wind only\n3: Disk wind only with a given minimum temperature\n4: Isothermal disk wind only\n5: Magnetosphere and disk wind\n6: Magnetosphere and disk wind with a mininum given temperature\n7: Magnetosphere and isothermal disk wind");
}

void CVInputData::on_lineEdit_83_editingFinished()
{
    setMagnetoHeatingRate(ui->lineEdit_83->text().toFloat());
}

void CVInputData::on_pushButton_60_clicked()
{
    QMessageBox::information(this, "Help!", "Heating rate that will be used to calculate the temperature inside the magnetosphere");
}

void CVInputData::on_lineEdit_84_editingFinished()
{
    setDiskwindHeatingRate(ui->lineEdit_84->text().toFloat());
}

void CVInputData::on_pushButton_61_clicked()
{
    QMessageBox::information(this, "Help!", "Heating rate that will be used to calculate the temperature inside the disk wind");
}

void CVInputData::on_lineEdit_85_editingFinished()
{
    setDiskwindTemp(ui->lineEdit_85->text().toFloat());
}

void CVInputData::on_pushButton_62_clicked()
{
    QMessageBox::information(this, "Help!", "Temperature inside the isothermic disk wind in [K]");
}

void CVInputData::on_lineEdit_86_editingFinished()
{
    setDiskwindMinTemperature(ui->lineEdit_86->text().toFloat());
}

void CVInputData::on_pushButton_63_clicked()
{
    QMessageBox::information(this, "Help!", "Lowest possible temperature inside the disk wind in [K]");
}

void CVInputData::on_pushButton_64_clicked()
{
    QMessageBox::information(this, "Help!", "Keep intensity maps data");
}

void CVInputData::on_pushButton_65_clicked()
{
    QMessageBox::information(this, "Help!", "Do density correction in the disk wind grid. Should be used only in the disk wind only case");
}

void CVInputData::on_checkBox_2_clicked()
{
    setDoMap(ui->checkBox_2->isChecked());
}

void CVInputData::on_checkBox_clicked()
{
    setDcomp(ui->checkBox->isChecked());
}

void CVInputData::on_checkBox_3_clicked()
{
    setDoSurface(ui->checkBox_3->isChecked());
}

void CVInputData::on_actionSearch_Tool_triggered()
{
    QString args = "java -jar /home/samuel/Documents/CV/cvmod/CVDBConnector/dist/CV_DataBase.jar -S ";
    QProcess Search;
    Search.execute(args);
}
