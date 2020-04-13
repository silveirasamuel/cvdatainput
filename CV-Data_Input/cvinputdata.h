//By Samuel PP Silveira, Centro Federal de Educação Tecnológica de Minas Gerais, 2017

#ifndef CVINPUTDATA_H
#define CVINPUTDATA_H

#include <QMainWindow>
#include <QMessageBox>
using namespace std;

/*
 *This class to control the physical parameters on file "example.AATau"
 */
class Parameters {
private:
    //This is the scope of parameters

    QString verbose, auxverbose, specialI, specialJ,
    velocityLaw,
    atmosphereType,
    jobType,
    useGridFile, useTemperaturesOnly, gridFilename, surfacesFilename, velocityFilename, profVelFilename, atmosphereFilename,
    stellarRadInRsun, stellarMassInMsun, maxRadius,
    tempStar, tempRing, radiationTemp, tempGas, fixedEpsilon,
    useAtomFile, doMulti, element, atomFilename, lowerLevel, upperLevel,
    abundance, oscillator, cUpperlevel, aUpperlevel, frequency, wavelenght,
    lineDepth, lineDopplerWidth, lineWing,
    suppressRotation, doHotspot, hotspotphi1, hotspotphi2,
    diskwindInnerXo, diskwindOuterXo, diskwindZHeight, diskwindA, diskwindB, diskwindRho0, diskwindTdmax,
    densityFactor, massFlow, innerR0, outerR0, beq, polVelInner, omegask, xlin,
    rhTau0,
    maxIteration, nSourceX, nSourceZ, nSourcePhi, nSourceTheta, nSourceStep, sourceThetastarFrac,
    profVelFactor, nprofileVelocity, nprofileAngle, nprofileRadii, nprofileStarRadii, nprofileStep, firstVelocity, lastVelocity, inclination,
    usedSavedSurfaces, saveSurfaces, useSavedSource, saveSource, doProfile, doIoneql;
    //These are the script parameters scope
    float starDiskInclination, magnetoHeatingRate, diskwindHeatingRate, diskwindTemp, diskwindMinTemperature;
    QString nameStar;
    bool doSurface, doMap, dcomp;
    int tempType;

    //This is the name of exit file
    QString outFileName;
public:
    QString FILEEXITADRESS;
    Parameters(){
        FILEEXITADRESS = "/home/samuel/Documents/CV/cvmod/newconfig.";
        verbose="8";
        auxverbose="2";
        specialI="-1";
        specialJ="-1";

        velocityLaw="6";
        atmosphereType="1";
        jobType = "5";

        useGridFile="0";
        useTemperaturesOnly = "0";
        gridFilename="grid.dat";
        surfacesFilename="surfaces.ABAur";
        velocityFilename = "diskwindxcv_ABAur";
        profVelFilename="profveltable";
        atmosphereFilename="ABAur_Atmo.dat";

        stellarRadInRsun = "2.50";
        stellarMassInMsun = "2.40";
        maxRadius = "3.";

        tempStar = "9.6e3";
        tempRing = "9.6e3";
        radiationTemp = "9.6e3";
        tempGas ="4.0e3";
        fixedEpsilon = "-1.";

        useAtomFile = "1";
        doMulti = "0";
        element ="1";
        atomFilename="hydrogen.dat";
        lowerLevel="2";
        upperLevel="3";

        abundance = "1";
        oscillator="0.649";
        cUpperlevel="6.55e-8";
        aUpperlevel = "6.22e7";
        frequency = "0.";
        wavelenght="5.890e-5";

        lineDepth="0.0";
        lineDopplerWidth="100";
        lineWing="0.0";

        suppressRotation="0";
        doHotspot="0";
        hotspotphi1="0.";
        hotspotphi2="0.";

        diskwindInnerXo="5.000";
        diskwindOuterXo="25.00";
        diskwindZHeight="30.0";
        diskwindA = "0.530";
        diskwindB="-0.100";
        diskwindRho0="2.000e-10";
        diskwindTdmax="3.27e3";

        densityFactor ="1.";
        massFlow="1.64e19";
        innerR0="1.40";
        outerR0="2.00";
        beq="2.5e3";
        polVelInner="3.0e-3";
        omegask="0.26";
        xlin="1.34";

        rhTau0="0.1";
        maxIteration="4";
        nSourceX="40";
        nSourceZ="40";
        nSourcePhi="40";
        nSourceTheta="40";
        nSourceStep="500";
        sourceThetastarFrac="2";

        profVelFactor ="1.0";
        nprofileVelocity="60";
        nprofileAngle="40";
        nprofileRadii="50";
        nprofileStarRadii="20";
        nprofileStep="600";
        firstVelocity="-400.";
        lastVelocity="400.";
        inclination="90.0";

        usedSavedSurfaces="0";
        saveSurfaces="1";
        useSavedSource="0";
        saveSource="1";
        doProfile="0";
        doIoneql="0";
        //script variables
        starDiskInclination=20.;
        nameStar="";
        doSurface=false;
        tempType=0;
        magnetoHeatingRate=1.e-3;
        diskwindHeatingRate=1.e-4;
        diskwindTemp = 8000.;
        diskwindMinTemperature=4000.;
        doMap=false;
        dcomp=false;

    }
    void printConfigFile();

    void writeParameters();

    void run();

    void setStarDiskInclination(float starDiskInclination){
        this->starDiskInclination = starDiskInclination;
    }

    void setNameStar(QString nameStar){
        this->nameStar = nameStar;
    }

    void setDoSurface(bool doSurface){
        this->doSurface = doSurface;
    }

    void setTempType(int tempType){
       this->tempType = tempType;
    }

    int getTempType(){
        return tempType;
    }

    void setMagnetoHeatingRate(float magnetoHeatingRate){
        this->magnetoHeatingRate = magnetoHeatingRate;
    }

    void setDiskwindHeatingRate(float diskwindHeatingRate){
        this->diskwindHeatingRate = diskwindHeatingRate;
    }

    void setDiskwindTemp(float diskwindTemp){
        this->diskwindTemp = diskwindTemp;
    }

    void setDiskwindMinTemperature(float diskwindMinTemperature){
        this->diskwindMinTemperature = diskwindMinTemperature;
    }

    void setDoMap(bool doMap){
        this->doMap = doMap;
    }

    void setDcomp(bool dcomp){
        this->dcomp = dcomp;
    }

    void setAbundance(QString abundance) {
        this->abundance = abundance;
    }

    void setAtmosphereFilename(QString atmosphereFilename) {
        this->atmosphereFilename = atmosphereFilename;
    }

    void setAtmosphereType(QString atmosphereType) {
        this->atmosphereType = atmosphereType;
    }

    void setAtomFilename(QString atomFilename) {
        this->atomFilename = atomFilename;
    }

    void setAUpperlevel(QString aUpperlevel) {
        this->aUpperlevel = aUpperlevel;
    }

    void setAuxverbose(QString auxverbose) {
        this->auxverbose = auxverbose;
    }

    void setBeq(QString beq) {
        this->beq = beq;
    }

    void setCUpperlevel(QString cUpperlevel) {
        this->cUpperlevel = cUpperlevel;
    }

    void setDensityFactor(QString densityFactor) {
        this->densityFactor = densityFactor;
    }

    void setDiskwindA(QString diskwindA) {
        this->diskwindA = diskwindA;
    }

    void setDiskwindB(QString diskwindB) {
        this->diskwindB = diskwindB;
    }

    void setDiskwindInnerXo(QString diskwindInnerXo) {
        this->diskwindInnerXo = diskwindInnerXo;
    }

    void setDiskwindOuterXo(QString diskwindOuterXo) {
        this->diskwindOuterXo = diskwindOuterXo;
    }

    void setDiskwindRho0(QString diskwindRho0) {
        this->diskwindRho0 = diskwindRho0;
    }

    void setDiskwindTdmax(QString diskwindTdmax) {
        this->diskwindTdmax = diskwindTdmax;
    }

    void setDiskwindZHeight(QString diskwindZHeight) {
        this->diskwindZHeight = diskwindZHeight;
    }

    QString getDoHotspot() const {
        return doHotspot;
    }

    void setDoHotspot(QString doHotspot) {
        this->doHotspot = doHotspot;
    }

    void setDoIoneql(QString doIoneql) {
        this->doIoneql = doIoneql;
    }

    void setDoMulti(QString doMulti) {
        this->doMulti = doMulti;
    }

    void setDoProfile(QString doProfile) {
        this->doProfile = doProfile;
    }

    void setElement(QString element) {
        this->element = element;
    }

    void setFirstVelocity(QString firstVelocity) {
        this->firstVelocity = firstVelocity;
    }

    void setFixedEpsilon(QString fixedEpsilon) {
        this->fixedEpsilon = fixedEpsilon;
    }

    void setFrequency(QString frequency) {
        this->frequency = frequency;
    }

    void setGridFilename(QString gridFilename) {
        this->gridFilename = gridFilename;
    }

    void setHotspotphi1(QString hotspotphi1) {
        this->hotspotphi1 = hotspotphi1;
    }

    void setHotspotphi2(QString hotspotphi2) {
        this->hotspotphi2 = hotspotphi2;
    }

    void setInclination(QString inclination) {
        this->inclination = inclination;
    }

    void setInnerR0(QString innerR0) {
        this->innerR0 = innerR0;
    }

    void setJobType(QString jobType) {
        this->jobType = jobType;
    }

    void setLastVelocity(QString lastVelocity) {
        this->lastVelocity = lastVelocity;
    }

    void setLineDepth(QString lineDepth) {
        this->lineDepth = lineDepth;
    }

    void setLineDopplerWidth(QString lineDopplerWidth) {
        this->lineDopplerWidth = lineDopplerWidth;
    }

    void setLineWing(QString lineWing) {
        this->lineWing = lineWing;
    }

    void setLowerLevel(QString lowerLevel) {
        this->lowerLevel = lowerLevel;
    }

    void setMassFlow(QString massFlow) {
        this->massFlow = massFlow;
    }

    void setMaxIteration(QString maxIteration) {
        this->maxIteration = maxIteration;
    }

    void setMaxRadius(QString maxRadius) {
        this->maxRadius = maxRadius;
    }

    void setNprofileAngle(QString nprofileAngle) {
        this->nprofileAngle = nprofileAngle;
    }

    void setNprofileRadii(QString nprofileRadii) {
        this->nprofileRadii = nprofileRadii;
    }

    void setNprofileStarRadii(QString nprofileStarRadii) {
        this->nprofileStarRadii = nprofileStarRadii;
    }

    void setNprofileStep(QString nprofileStep) {
        this->nprofileStep = nprofileStep;
    }

    void setNprofileVelocity(QString nprofileVelocity) {
        this->nprofileVelocity = nprofileVelocity;
    }

    void setSourcePhi(QString sourcePhi) {
        nSourcePhi = sourcePhi;
    }

    void setSourceStep(QString sourceStep) {
        nSourceStep = sourceStep;
    }

    void setSourceTheta(QString sourceTheta) {
        nSourceTheta = sourceTheta;
    }

    void setSourceX(QString sourceX) {
        nSourceX = sourceX;
    }

    void setSourceZ(QString sourceZ) {
        nSourceZ = sourceZ;
    }

    void setOmegask(QString omegask) {
        this->omegask = omegask;
    }

    void setOscillator(QString oscillator) {
        this->oscillator = oscillator;
    }

    void setOuterR0(QString outerR0) {
        this->outerR0 = outerR0;
    }

    QString getOutFileName() const {
        return outFileName;
    }

    void setOutFileName(QString outFileName) {
        this->outFileName = outFileName;
    }

    void setPolVelInner(QString polVelInner) {
        this->polVelInner = polVelInner;
    }

    void setProfVelFactor(QString profVelFactor) {
        this->profVelFactor = profVelFactor;
    }

    void setProfVelFilename(QString profVelFilename) {
        this->profVelFilename = profVelFilename;
    }

    void setRadiationTemp(QString radiationTemp) {
        this->radiationTemp = radiationTemp;
    }

    void setRhTau0(QString rhTau0) {
        this->rhTau0 = rhTau0;
    }

    void setSaveSource(QString saveSource) {
        this->saveSource = saveSource;
    }

    void setSaveSurfaces(QString saveSurfaces) {
        this->saveSurfaces = saveSurfaces;
    }

    void setSourceThetastarFrac(QString sourceThetastarFrac) {
        this->sourceThetastarFrac = sourceThetastarFrac;
    }

    void setSpecialI(QString specialI) {
        this->specialI = specialI;
    }

    void setSpecialJ(QString specialJ) {
        this->specialJ = specialJ;
    }

    void setStellarMassInMsun(QString stellarMassInMsun) {
        this->stellarMassInMsun = stellarMassInMsun;
    }

    void setStellarRadInRsun(QString stellarRadInRsun) {
        this->stellarRadInRsun = stellarRadInRsun;
    }

    void setSuppressRotation(QString suppressRotation) {
        this->suppressRotation = suppressRotation;
    }

    void setSurfacesFilename(QString surfacesFilename) {
        this->surfacesFilename = surfacesFilename;
    }

    void setTempGas(QString tempGas) {
        this->tempGas = tempGas;
    }

    void setTempRing(QString tempRing) {
        this->tempRing = tempRing;
    }

    void setTempStar(QString tempStar) {
        this->tempStar = tempStar;
    }

    void setUpperLevel(QString upperLevel) {
        this->upperLevel = upperLevel;
    }

    void setUseAtomFile(QString useAtomFile) {
        this->useAtomFile = useAtomFile;
    }

    void setUsedSavedSurfaces(QString usedSavedSurfaces) {
        this->usedSavedSurfaces = usedSavedSurfaces;
    }

    void setUseGridFile(QString useGridFile) {
        this->useGridFile = useGridFile;
    }

    void setUseSavedSource(QString useSavedSource) {
        this->useSavedSource = useSavedSource;
    }

    void setUseTemperaturesOnly(QString useTemperaturesOnly) {
        this->useTemperaturesOnly = useTemperaturesOnly;
    }

    void setVelocityFilename(QString velocityFilename) {
        this->velocityFilename = velocityFilename;
    }

    void setVelocityLaw(QString velocityLaw) {
        this->velocityLaw = velocityLaw;
    }

    void setVerbose(QString verbose) {
        this->verbose = verbose;
    }

    void setWavelenght(QString wavelenght) {
        this->wavelenght = wavelenght;
    }

    void setXlin(QString xlin) {
        this->xlin = xlin;
    }

    QString getNameStar(){
        return nameStar;
    }
};


namespace Ui {
class CVInputData;
}

class CVInputData : public QMainWindow, public Parameters
{
    Q_OBJECT

public:
    explicit CVInputData(QWidget *parent = 0);
    ~CVInputData();



private slots:

    void on_pushButton_2_clicked();

    void on_lineEdit_4_editingFinished();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_lineEdit_7_editingFinished();

    void on_pushButton_6_clicked();

    void on_lineEdit_8_editingFinished();

    void on_pushButton_7_clicked();

    void on_lineEdit_9_editingFinished();

    void on_pushButton_8_clicked();

    void on_lineEdit_10_editingFinished();

    void on_pushButton_9_clicked();

    void on_lineEdit_11_editingFinished();

    void on_pushButton_10_clicked();

    void on_pushButton_11_clicked();

    void on_actionExit_triggered();

    void on_actionInstructions_triggered();

    void on_lineEdit_13_editingFinished();

    void on_pushButton_13_clicked();

    void on_lineEdit_14_editingFinished();

    void on_pushButton_14_clicked();

    void on_lineEdit_15_editingFinished();

    void on_pushButton_15_clicked();

    void on_ExitFileLine_editingFinished();

    void on_VerboseButton_clicked();

    void on_AuxVerboseButton_clicked();

    void on_lineEdit_editingFinished();

    void on_lineEdit_2_editingFinished();

    void on_lineEdit_3_editingFinished();

    void on_lineEdit_5_editingFinished();

    void on_lineEdit_6_editingFinished();

    void on_pushButton_clicked();

    void on_lineEdit_16_editingFinished();

    void on_pushButton_12_clicked();

    void on_lineEdit_17_editingFinished();

    void on_lineEdit_18_editingFinished();

    void on_pushButton_16_clicked();

    void on_pushButton_17_clicked();

    void on_lineEdit_19_editingFinished();

    void on_pushButton_18_clicked();

    void on_lineEdit_20_editingFinished();

    void on_pushButton_19_clicked();

    void on_lineEdit_21_editingFinished();

    void on_pushButton_20_clicked();

    void on_lineEdit_22_editingFinished();

    void on_pushButton_21_clicked();

    void on_lineEdit_23_editingFinished();

    void on_pushButton_22_clicked();

    void on_lineEdit_24_editingFinished();

    void on_pushButton_23_clicked();

    void on_lineEdit_25_editingFinished();

    void on_pushButton_24_clicked();

    void on_lineEdit_26_editingFinished();

    void on_pushButton_25_clicked();

    void on_lineEdit_27_editingFinished();

    void on_pushButton_26_clicked();

    void on_lineEdit_28_editingFinished();

    void on_pushButton_27_clicked();

    void on_lineEdit_29_editingFinished();

    void on_pushButton_28_clicked();

    void on_lineEdit_30_editingFinished();


    void on_lineEdit_31_editingFinished();

    void on_lineEdit_32_editingFinished();

    void on_lineEdit_33_editingFinished();

    void on_pushButton_29_clicked();

    void on_lineEdit_34_editingFinished();

    void on_pushButton_30_clicked();

    void on_lineEdit_35_editingFinished();

    void on_lineEdit_36_editingFinished();

    void on_pushButton_31_clicked();

    void on_pushButton_32_clicked();

    void on_lineEdit_37_editingFinished();

    void on_lineEdit_38_editingFinished();

    void on_lineEdit_39_editingFinished();

    void on_lineEdit_40_editingFinished();

    void on_pushButton_33_clicked();

    void on_lineEdit_41_editingFinished();

    void on_pushButton_34_clicked();

    void on_lineEdit_42_editingFinished();

    void on_lineEdit_43_editingFinished();

    void on_lineEdit_44_editingFinished();

    void on_lineEdit_45_editingFinished();

    void on_lineEdit_46_editingFinished();

    void on_lineEdit_47_editingFinished();

    void on_lineEdit_48_editingFinished();

    void on_lineEdit_49_editingFinished();

    void on_pushButton_35_clicked();

    void on_lineEdit_50_editingFinished();

    void on_pushButton_36_clicked();

    void on_lineEdit_51_editingFinished();

    void on_pushButton_37_clicked();

    void on_lineEdit_52_editingFinished();

    void on_pushButton_38_clicked();

    void on_lineEdit_53_editingFinished();

    void on_pushButton_39_clicked();

    void on_lineEdit_54_editingFinished();

    void on_pushButton_40_clicked();

    void on_lineEdit_55_editingFinished();

    void on_pushButton_41_clicked();

    void on_lineEdit_56_editingFinished();

    void on_pushButton_42_clicked();

    void on_lineEdit_57_editingFinished();

    void on_lineEdit_58_editingFinished();

    void on_pushButton_43_clicked();

    void on_lineEdit_59_editingFinished();

    void on_lineEdit_60_editingFinished();

    void on_lineEdit_61_editingFinished();

    void on_lineEdit_62_editingFinished();

    void on_lineEdit_63_editingFinished();

    void on_pushButton_44_clicked();

    void on_lineEdit_64_editingFinished();

    void on_pushButton_45_clicked();

    void on_lineEdit_65_editingFinished();

    void on_pushButton_46_clicked();

    void on_lineEdit_66_editingFinished();

    void on_lineEdit_67_editingFinished();

    void on_lineEdit_68_editingFinished();

    void on_pushButton_47_clicked();

    void on_lineEdit_69_editingFinished();

    void on_lineEdit_70_editingFinished();

    void on_pushButton_48_clicked();

    void on_lineEdit_71_editingFinished();

    void on_pushButton_49_clicked();

    void on_lineEdit_72_editingFinished();

    void on_lineEdit_73_editingFinished();

    void on_pushButton_50_clicked();

    void on_pushButton_51_clicked();

    void on_lineEdit_74_editingFinished();

    void on_pushButton_52_clicked();

    void on_lineEdit_75_editingFinished();

    void on_lineEdit_76_editingFinished();

    void on_pushButton_53_clicked();

    void on_lineEdit_77_editingFinished();

    void on_pushButton_54_clicked();

    void on_lineEdit_78_editingFinished();

    void on_lineEdit_79_editingFinished();

    void on_pushButton_55_clicked();

    void on_pushButton_56_clicked();

    void on_lineEdit_80_editingFinished();

    void on_lineEdit_81_editingFinished();

    void on_pushButton_57_clicked();

    void on_pushButton_58_clicked();

    void on_lineEdit_82_editingFinished();

    void on_pushButton_59_clicked();

    void on_lineEdit_83_editingFinished();

    void on_pushButton_60_clicked();

    void on_lineEdit_84_editingFinished();

    void on_pushButton_61_clicked();

    void on_lineEdit_85_editingFinished();

    void on_pushButton_62_clicked();

    void on_lineEdit_86_editingFinished();

    void on_pushButton_63_clicked();

    void on_pushButton_64_clicked();

    void on_pushButton_65_clicked();

    void on_checkBox_2_clicked();

    void on_checkBox_clicked();

    void on_checkBox_3_clicked();

    void on_actionSearch_Tool_triggered();

private:
    Ui::CVInputData *ui;
};






#endif // CVINPUTDATA_H
