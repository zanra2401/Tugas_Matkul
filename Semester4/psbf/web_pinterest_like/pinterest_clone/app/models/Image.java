package models;

import play.db.Database;
import java.sql.*;
import javax.inject.Inject;
import java.util.List;
import java.util.ArrayList;


public class Image {

    private final Database db;

    @Inject
    public Image(Database db) {
        this.db = db;
    }

    // CREATE
    public boolean uploadImage(String fileName, String filePath) {
        String query = "INSERT INTO images (filename, filepath) VALUES (?, ?)";
        
        try (Connection conn = db.getConnection(); 
             PreparedStatement stmt = conn.prepareStatement(query)) {
            
            stmt.setString(1, fileName);
            stmt.setString(2, filePath);
            stmt.executeUpdate();
            return true;
        } catch (SQLException e) {
            e.printStackTrace();
            return false;
        }
    }

    // READ
    public ImageData getImage(Long id) {
        String query = "SELECT * FROM images WHERE id = ?";
        ImageData image = null;

        try (Connection conn = db.getConnection();
             PreparedStatement stmt = conn.prepareStatement(query)) {

            stmt.setLong(1, id);
            ResultSet rs = stmt.executeQuery();

            if (rs.next()) {
                image = new ImageData(rs.getLong("id"), rs.getString("filename"), rs.getString("filepath"));
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }

        return image;
    }

    // READ All
    public List<ImageData> getAllImages() {
        String query = "SELECT * FROM images";
        List<ImageData> images = new ArrayList<>();

        try (Connection conn = db.getConnection();
             PreparedStatement stmt = conn.prepareStatement(query);
             ResultSet rs = stmt.executeQuery()) {

            while (rs.next()) {
                images.add(new ImageData(rs.getLong("id"), rs.getString("filename"), rs.getString("filepath")));
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }

        return images;
    }

    // UPDATE
    public boolean updateImage(Long id, String newFileName, String newFilePath) {
        String query = "UPDATE images SET filename = ?, filepath = ? WHERE id = ?";

        try (Connection conn = db.getConnection();
             PreparedStatement stmt = conn.prepareStatement(query)) {

            stmt.setString(1, newFileName);
            stmt.setString(2, newFilePath);
            stmt.setLong(3, id);
            stmt.executeUpdate();
            return true;
        } catch (SQLException e) {
            e.printStackTrace();
            return false;
        }
    }

    // DELETE
    public boolean deleteImage(Long id) {
        String query = "DELETE FROM images WHERE id = ?";

        try (Connection conn = db.getConnection();
             PreparedStatement stmt = conn.prepareStatement(query)) {

            stmt.setLong(1, id);
            stmt.executeUpdate();
            return true;
        } catch (SQLException e) {
            e.printStackTrace();
            return false;
        }
    }

    public static class ImageData {
        private Long id;
        private String fileName;
        private String filePath;

        public ImageData(Long id, String fileName, String filePath) {
            this.id = id;
            this.fileName = fileName;
            this.filePath = filePath;
        }

        public Long getId() {
            return id;
        }

        public String getFileName() {
            return fileName;
        }

        public String getFilePath() {
            return filePath;
        }
    }
}
