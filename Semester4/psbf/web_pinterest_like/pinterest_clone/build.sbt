name := """pinterest_clone"""
organization := "com.hari_selasa_rungkad"

version := "1.0-SNAPSHOT"

lazy val root = (project in file(".")).enablePlugins(PlayJava)

scalaVersion := "2.13.16"

libraryDependencies += guice

libraryDependencies ++= Seq(
  jdbc,
  "mysql" % "mysql-connector-java" % "8.0.33"
)

