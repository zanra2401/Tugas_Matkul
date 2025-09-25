package controllers;

import play.mvc.*;
import play.mvc.Http.*;
import play.libs.Files.TemporaryFile;
import play.db.Database;
import play.mvc.Http.MultipartFormData.FilePart;
import javax.inject.Inject;


import models.Image;

import java.io.File;
import java.sql.SQLException;

/**
 * This controller contains an action to handle HTTP requests
 * to the application's home page.
 */
public class Pinterest extends Controller {

    /**
     * An action that renders an HTML page with a welcome message.
     * The configuration in the <code>routes</code> file means that
     * this method will be called when the application receives a
     * <code>GET</code> request with a path of <code>/</code>.
     */

    private final Image imageModel;
    private final Database db;

    @Inject
    public Pinterest(Database db) {
        this.db = db;
        this.imageModel = new Image(db);
    }

    public Result index() {
        return ok(views.html.index.render());
    }

    public Result profile() {
        return ok(views.html.profile.render());
    }

    public Result upload() {
        return ok(views.html.profile.render());
    }
}
