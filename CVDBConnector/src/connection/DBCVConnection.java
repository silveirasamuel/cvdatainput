package connection;

import java.io.FileNotFoundException;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.Formatter;
import java.util.List;
import java.util.logging.Level;
import java.util.logging.Logger;

class Star {

    String name;
    double mass, radius, systemInclination;
    String usingAtmosphericModel;
    double mginnerRadius, mgouterRadius, mgmassAccretionRate, mgheatingRate, mgminimumTemperature, dwHeatingRate, dwMinTemperature, mgmaximumTemperature, dwinnerRadius, dwouterRadius, dwmaximumHeight, dwCoeficientA, dwCoeficientB, dwLauchingAngle, lambda, kappa, fiducialDensity, massLossRate, isothermalDiskWindTemperature, transitionLowerLevel, transitionUpperLevel, centralLineFrequency;
    String timeStamp;

    Star() {

    }

    Star(String name,
            double mass, double radius, double systemInclination,
            String usingAtmosphericModel,
            double mginnerRadius, double mgouterRadius, double mgmassAccretionRate, double mgheatingRate, double mgminimumTemperature, double mgmaximumTemperature, double dwinnerRadius, double dwouterRadius, double dwHeatingRate, double dwMinTemperature, double dwmaximumHeight, double dwCoeficientA, double dwCoeficientB, double dwLauchingAngle, double lambda, double kappa, double fiducialDensity, double massLossRate, double isothermalDiskWindTemperature, double transitionLowerLevel, double transitionUpperLevel, double centralLineFrequency,
            String timeStamp) {

        this.name = name;
        this.mass = mass;
        this.radius = radius;
        this.systemInclination = systemInclination;
        this.usingAtmosphericModel = usingAtmosphericModel;
        this.mginnerRadius = mginnerRadius;
        this.mgouterRadius = mgouterRadius;
        this.mgmassAccretionRate = mgmassAccretionRate;
        this.mgheatingRate = mgheatingRate;
        this.mgminimumTemperature = mgminimumTemperature;
        this.mgmaximumTemperature = mgmaximumTemperature;
        this.dwinnerRadius = dwinnerRadius;
        this.dwouterRadius = dwouterRadius;
        this.dwHeatingRate = dwHeatingRate;
        this.dwMinTemperature = dwMinTemperature;
        this.dwmaximumHeight = dwmaximumHeight;
        this.dwCoeficientA = dwCoeficientA;
        this.dwCoeficientB = dwCoeficientB;
        this.dwLauchingAngle = dwLauchingAngle;
        this.lambda = lambda;
        this.kappa = kappa;
        this.fiducialDensity = fiducialDensity;
        this.massLossRate = massLossRate;
        this.isothermalDiskWindTemperature = isothermalDiskWindTemperature;
        this.transitionLowerLevel = transitionLowerLevel;
        this.transitionUpperLevel = transitionUpperLevel;
        this.centralLineFrequency = centralLineFrequency;
        this.timeStamp = timeStamp;
    }

}

public class DBCVConnection {

    private final String nomeJDBC = "jdbc:mysql://localhost/CV Stars";
    private final String nomeUser = "root";
    private final String password = "";
    private Connection con;
    private PreparedStatement st;

    public boolean openConnection() {
        try {
            Class.forName("com.mysql.jdbc.Driver");

            con = DriverManager.getConnection(nomeJDBC, nomeUser, password);
        } catch (ClassNotFoundException | SQLException ex) {
            ex.printStackTrace();
            return false;
        }

        return true;
    }

    public void closeConnection() {
        try {
            con.close();
        } catch (SQLException ex) {
            ex.printStackTrace();
        }
    }

    public List<Star> searchStars(Star star) {
        String sql = "SELECT * FROM `Star` WHERE name = \"" + star.name + "\" AND mass = " + star.mass + " AND radius = " + star.radius + " AND system_inclination = " + star.systemInclination + " AND using_atmospheric_model = \"" + star.usingAtmosphericModel + "\" AND mag_inner_radius = " + star.mginnerRadius + " AND mag_outer_radius = " + star.mgouterRadius + " AND mag_mass_accretion_rate = " + star.mgmassAccretionRate + " AND mag_heating_rate = " + star.mgheatingRate + " AND diskwind_inner_radius  = " + star.dwinnerRadius + " AND diskwind_outer_radius = " + star.dwouterRadius + " AND dwHeatingRate = " + star.dwHeatingRate + " AND dwMinTemperature = " + star.dwMinTemperature + " AND diskwind_maximum_height = " + star.dwmaximumHeight + " AND coeficient_a = " + star.dwCoeficientA + " AND coeficient_b = " + star.dwCoeficientB + " AND lambda = " + star.lambda + " AND kappa = " + star.kappa + " AND fiducial_density = " + star.fiducialDensity + " AND isothermal_disk_wind_temperature = " + star.isothermalDiskWindTemperature + " AND transition_lower_level = " + star.transitionLowerLevel + " AND transition_upper_level = " + star.transitionUpperLevel;
        //String sql = "SELECT * FROM `Star`";
        List<Star> list = new ArrayList<Star>();
        //System.out.println(sql);
        Star stars;
        try {

            st = con.prepareStatement(sql);
            st.execute();

            ResultSet table = st.getResultSet();
            while (table.next()) {
                stars = new Star();
                stars.name = table.getString("name");
                stars.mass = table.getDouble("mass");
                stars.radius = table.getDouble("radius");
                stars.systemInclination = table.getDouble("system_inclination");
                stars.usingAtmosphericModel = table.getString("using_atmospheric_model");
                stars.mginnerRadius = table.getDouble("mag_inner_radius");
                stars.mgouterRadius = table.getDouble("mag_outer_radius");
                stars.mgmassAccretionRate = table.getDouble("mag_mass_accretion_rate");
                stars.mgheatingRate = table.getDouble("mag_heating_rate");
                stars.mgminimumTemperature = table.getDouble("mag_minimum_temperature");
                stars.mgmaximumTemperature = table.getDouble("mag_maximum_temperature");
                stars.dwHeatingRate = table.getDouble("dwHeatingRate");
                stars.dwMinTemperature = table.getDouble("dwMinTemperature");
                stars.dwinnerRadius = table.getDouble("diskwind_inner_radius");
                stars.dwouterRadius = table.getDouble("diskwind_outer_radius");
                stars.dwmaximumHeight = table.getDouble("diskwind_maximum_height");
                stars.dwCoeficientA = table.getDouble("coeficient_a");
                stars.dwCoeficientB = table.getDouble("coeficient_b");
                stars.dwLauchingAngle = table.getDouble("disk_wind_lauching_angle");
                stars.lambda = table.getDouble("lambda");
                stars.kappa = table.getDouble("kappa");
                stars.fiducialDensity = table.getDouble("fiducial_density");
                stars.massLossRate = table.getDouble("mass_loss_rate");
                stars.isothermalDiskWindTemperature = table.getDouble("isothermal_disk_wind_temperature");
                stars.transitionLowerLevel = table.getDouble("transition_lower_level");
                stars.transitionUpperLevel = table.getDouble("transition_upper_level");
                stars.centralLineFrequency = table.getDouble("central_line_frequency");
                stars.timeStamp = table.getString("time_stamp");
                list.add(stars);
            }
            Formatter arquivo;

            try {
                arquivo = new Formatter("StarExists." + star.timeStamp);
                if (list.isEmpty()) {
                    arquivo.format("0");
                } else {
                    arquivo.format("1\n"+list.get(0).timeStamp);
                }

                arquivo.close();
            } catch (FileNotFoundException ex) {
                Logger.getLogger(DBCVConnection.class.getName()).log(Level.SEVERE, null, ex);
            }

            return list;
        } catch (SQLException ex) {
            ex.printStackTrace();
        }

        return list;
    }

    public void inputStar(Star star) {
        try {
            String sql = "INSERT INTO `Star`(`name`, `mass`, `radius`, `system_inclination`, `using_atmospheric_model`, `mag_inner_radius`, `mag_outer_radius`, `mag_mass_accretion_rate`, `mag_heating_rate`, `mag_minimum_temperature`, `mag_maximum_temperature`, `diskwind_inner_radius`, `diskwind_outer_radius`, `dwHeatingRate`, `dwMinTemperature`, `diskwind_maximum_height`, `coeficient_a`, `coeficient_b`, `disk_wind_lauching_angle`, `lambda`, `kappa`, `fiducial_density`, `mass_loss_rate`, `isothermal_disk_wind_temperature`, `transition_lower_level`, `transition_upper_level`, `central_line_frequency`,`time_stamp`) "
                    + "VALUES (?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?)";
            st = con.prepareStatement(sql);
            st.setString(1, star.name);
            st.setDouble(2, star.mass);
            st.setDouble(3, star.radius);
            st.setDouble(4, star.systemInclination);
            st.setString(5, star.usingAtmosphericModel);
            st.setDouble(6, star.mginnerRadius);
            st.setDouble(7, star.mgouterRadius);
            st.setDouble(8, star.mgmassAccretionRate);
            st.setDouble(9, star.mgheatingRate);
            st.setDouble(10, star.mgminimumTemperature);
            st.setDouble(11, star.mgmaximumTemperature);
            st.setDouble(12, star.dwinnerRadius);
            st.setDouble(13, star.dwouterRadius);
            st.setDouble(14, star.dwHeatingRate);
            st.setDouble(15, star.dwMinTemperature);
            st.setDouble(16, star.dwmaximumHeight);
            st.setDouble(17, star.dwCoeficientA);
            st.setDouble(18, star.dwCoeficientB);
            st.setDouble(19, star.dwLauchingAngle);
            st.setDouble(20, star.lambda);
            st.setDouble(21, star.kappa);
            st.setDouble(22, star.fiducialDensity);
            st.setDouble(23, star.massLossRate);
            st.setDouble(24, star.isothermalDiskWindTemperature);
            st.setDouble(25, star.transitionLowerLevel);
            st.setDouble(26, star.transitionUpperLevel);
            st.setDouble(27, star.centralLineFrequency);
            st.setString(28, star.timeStamp);

            st.execute();
            st.close();

        } catch (SQLException ex) {
            ex.printStackTrace();
        }

    }

    public DBCVConnection() {

    }

    public static void main(String[] args) {

       
        
        DBCVConnection dbconnection = new DBCVConnection();
        dbconnection.openConnection();
        Star star;
        star = new Star(args[1], Double.parseDouble(args[2]), Double.parseDouble(args[3]), Double.parseDouble(args[4]), args[5], Double.parseDouble(args[6]), Double.parseDouble(args[7]), Double.parseDouble(args[8]), Double.parseDouble(args[9]), Double.parseDouble(args[10]), Double.parseDouble(args[11]), Double.parseDouble(args[12]), Double.parseDouble(args[13]), Double.parseDouble(args[14]), Double.parseDouble(args[15]), Double.parseDouble(args[16]), Double.parseDouble(args[17]), Double.parseDouble(args[18]), Double.parseDouble(args[19]), Double.parseDouble(args[20]), Double.parseDouble(args[21]), Double.parseDouble(args[22]), Double.parseDouble(args[23]), Double.parseDouble(args[24]), Double.parseDouble(args[25]), Double.parseDouble(args[26]), Double.parseDouble(args[27]), args[28]);
        switch (args[0]) {

            case "-s":
                List<Star> stars = dbconnection.searchStars(star);
                stars.stream().forEach((st) -> {
                    System.out.println("Star: " + st.name + "," + st.mass + "," + st.radius + "," + st.systemInclination + "," + st.usingAtmosphericModel + "," + st.mginnerRadius + "," + st.mgouterRadius + "," + st.mgmassAccretionRate + "," + st.mgheatingRate + "," + st.mgminimumTemperature + "," + st.mgmaximumTemperature + "," + st.dwHeatingRate + "," + st.dwMinTemperature + "," + st.dwinnerRadius + "," + st.dwouterRadius + "," + st.dwmaximumHeight + "," + st.dwCoeficientA + "," + st.dwCoeficientB + "," + st.dwLauchingAngle + "," + st.lambda + "," + st.kappa + "," + st.fiducialDensity + "," + st.massLossRate + "," + st.isothermalDiskWindTemperature + "," + st.transitionLowerLevel + "," + +st.transitionUpperLevel + "," + st.centralLineFrequency + "," + st.timeStamp + ".");
                });
                break;
            case "-i":
                dbconnection.inputStar(star);
                break;
            default:
                System.out.println("No option selected");
                break;
        }

        dbconnection.closeConnection();
    }

}
