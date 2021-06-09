/*
 Navicat Premium Data Transfer

 Source Server         : mysql
 Source Server Type    : MySQL
 Source Server Version : 50555
 Source Host           : localhost:3306
 Source Schema         : sboot

 Target Server Type    : MySQL
 Target Server Version : 50555
 File Encoding         : 65001

 Date: 09/06/2021 10:09:52
*/

SET NAMES utf8mb4;
SET FOREIGN_KEY_CHECKS = 0;

-- ----------------------------
-- Table structure for tbl_dept
-- ----------------------------
DROP TABLE IF EXISTS `tbl_dept`;
CREATE TABLE `tbl_dept`  (
  `deptid` int(2) NOT NULL,
  `deptname` varchar(20) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL,
  `location` varchar(50) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL,
  PRIMARY KEY (`deptid`) USING BTREE
) ENGINE = InnoDB CHARACTER SET = utf8 COLLATE = utf8_general_ci ROW_FORMAT = Compact;

-- ----------------------------
-- Records of tbl_dept
-- ----------------------------
INSERT INTO `tbl_dept` VALUES (0, '土木工程学院', '0');
INSERT INTO `tbl_dept` VALUES (1, '机械工程学院', '0');
INSERT INTO `tbl_dept` VALUES (2, '经济学院', '0');
INSERT INTO `tbl_dept` VALUES (3, '文法学院', '0');
INSERT INTO `tbl_dept` VALUES (4, '交通运输学院', '0');
INSERT INTO `tbl_dept` VALUES (5, '建筑与艺术学院', '0');
INSERT INTO `tbl_dept` VALUES (6, '电气与电子工程学院', '0');
INSERT INTO `tbl_dept` VALUES (7, '信息科学与技术学院', '0');
INSERT INTO `tbl_dept` VALUES (8, '工程力学系', '0');
INSERT INTO `tbl_dept` VALUES (9, '数理系', '0');
INSERT INTO `tbl_dept` VALUES (10, '外语系', '0');
INSERT INTO `tbl_dept` VALUES (11, '管理学院', '0');
INSERT INTO `tbl_dept` VALUES (12, '医学院', '0');

SET FOREIGN_KEY_CHECKS = 1;
