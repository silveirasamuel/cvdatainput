-- phpMyAdmin SQL Dump
-- version 4.7.2
-- https://www.phpmyadmin.net/
--
-- Host: localhost
-- Generation Time: 05-Set-2017 às 00:59
-- Versão do servidor: 10.1.26-MariaDB
-- PHP Version: 7.1.8

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
SET AUTOCOMMIT = 0;
START TRANSACTION;
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Database: `CVDataBase`
--

-- --------------------------------------------------------

--
-- Estrutura da tabela `Star`
--

CREATE TABLE `Star` (
  `name` varchar(10) NOT NULL,
  `mass` double NOT NULL,
  `radius` double NOT NULL,
  `system_inclination` double NOT NULL,
  `using_atmospheric_model` varchar(45) NOT NULL,
  `mag_inner_radius` double NOT NULL,
  `mag_outer_radius` double NOT NULL,
  `mag_mass_accretion_rate` double NOT NULL,
  `mag_heating_rate` double NOT NULL,
  `mag_minimum_temperature` double NOT NULL,
  `mag_maximum_temperature` double NOT NULL,
  `diskwind_inner_radius` double NOT NULL,
  `diskwind_outer_radius` double NOT NULL,
  `diskwind_maximum_height` double NOT NULL,
  `coeficient_a` double NOT NULL,
  `coeficient_b` double NOT NULL,
  `disk_wind_lauching_angle` double NOT NULL,
  `lambda` double NOT NULL,
  `kappa` double NOT NULL,
  `fiducial_density` double NOT NULL,
  `mass_loss_rate` double NOT NULL,
  `isothermal_disk_wind_temperature` double NOT NULL,
  `transition_lower_level` double NOT NULL,
  `transition_upper_level` double NOT NULL,
  `central_line_frequency` double NOT NULL,
  `grid_size` varchar(20) NOT NULL,
  `time_stamp` varchar(45) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- Extraindo dados da tabela `Star`
--

INSERT INTO `Star` (`name`, `mass`, `radius`, `system_inclination`, `using_atmospheric_model`, `mag_inner_radius`, `mag_outer_radius`, `mag_mass_accretion_rate`, `mag_heating_rate`, `mag_minimum_temperature`, `mag_maximum_temperature`, `diskwind_inner_radius`, `diskwind_outer_radius`, `diskwind_maximum_height`, `coeficient_a`, `coeficient_b`, `disk_wind_lauching_angle`, `lambda`, `kappa`, `fiducial_density`, `mass_loss_rate`, `isothermal_disk_wind_temperature`, `transition_lower_level`, `transition_upper_level`, `central_line_frequency`, `grid_size`, `time_stamp`) VALUES
('ABAur', 2.4, 2.5, 20, 'ABAur_Atmo.dat', 1.4, 2, 0.000000260208, 0.001, 5085.48, 6963.63, 5, 25, 30, 0.53, -0.1, 43.8309, 20, 0.06, 0.0000000002, 0.0000000339854, 8000, 2, 3, 456680000000000, '821 x 595', '2070831_141957');

--
-- Indexes for dumped tables
--

--
-- Indexes for table `Star`
--
ALTER TABLE `Star`
  ADD PRIMARY KEY (`time_stamp`);
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
