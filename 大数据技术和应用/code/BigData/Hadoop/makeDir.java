package hadoop.test;

import org.apache.hadoop.conf.Configuration;
import org.apache.hadoop.fs.FSDataOutputStream;
import org.apache.hadoop.fs.FileSystem;
import org.apache.hadoop.fs.Path;
import org.junit.Test;

import java.io.IOException;
import java.net.URI;
import java.net.URISyntaxException;

public class makeDir {

    public static void main(String[] args) throws URISyntaxException, IOException {
        Configuration configuration = new Configuration();
        String hdfsPath = "hdfs://localhost:9000";
        FileSystem hdfs = FileSystem.get(new URI(hdfsPath), configuration);

        String newDir = "/hdfsTest/touchFile";
        FSDataOutputStream rst = hdfs.create(new Path(newDir));

        System.out.println("Finish!!");
    }

    @Test
    void createFile() throws URISyntaxException, IOException {
        Configuration configuration = new Configuration();
        String hdfsPath = "hdfs://localhost:9000";
        FileSystem hdfs = FileSystem.get(new URI(hdfsPath), configuration);

        String newDir = "/hdfsTest/touchFile";
        FSDataOutputStream rst = hdfs.create(new Path(newDir));

        System.out.println("Finish!!");
    }

}