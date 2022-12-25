package hadoop.test;

import org.apache.hadoop.conf.Configuration;
import org.apache.hadoop.fs.*;
import org.junit.Before;
import org.junit.Test;

import java.io.IOException;
import java.net.URI;
import java.net.URISyntaxException;

public class TestBasicFunction {

    private Configuration configuration;
    private String hdfsPath;
    private FileSystem hdfs;
    private FileSystem local;

    @Before
    public void init() throws URISyntaxException, IOException {
        configuration = new Configuration();
        hdfsPath = "hdfs://localhost:9000";
        hdfs = FileSystem.get(new URI(hdfsPath), configuration);
        local = FileSystem.getLocal(configuration);
    }

    /**
     * merge all fils under local : /data/in
     * into hdfs: hdfsTest/mergeFile
     * @throws IOException
     */
    @Test
    public void mergeFile() throws IOException {
        String fromLinuxDir = "/data/in";
        String toHdfs = "/hdfsTest/mergeFile";
        FileStatus[] inputFiles = local.listStatus(new Path(fromLinuxDir));
        FSDataOutputStream out = hdfs.create(new Path(toHdfs));
        for (FileStatus file : inputFiles){
            FSDataInputStream in = local.open(file.getPath());
            byte[] buffer = new byte[256];
            int bytesRead = 0;
            while ((bytesRead = in.read(buffer)) > 0){
                out.write(buffer, 0, bytesRead);
            }
            in.close();
        }
        System.out.println("Finish!");
    }

    /**
     * create files and append text
     */
    @Test
    public void writeFile() throws IOException {
        String filePath = "/hdfsTest/writeFile";
        FSDataOutputStream create = hdfs.create(new Path(filePath));
        System.out.println("Step 1 Complete!");
        String sayHi = "Hello World hello data!";
        byte[] buff = sayHi.getBytes();
        create.write(buff, 0, buff.length);
        create.close();
        System.out.println("Step 2 Complete!");
    }



    /**
     * check file block info of '/hdfsTest/sample_data'
     */
    @Test
    public void locateFile() throws IOException {
        Path file = new Path("/hdfsTest/sample_data");
        FileStatus fileStatus = hdfs.getFileStatus(file);
        BlockLocation[] locations = hdfs.getFileBlockLocations(fileStatus, 0, fileStatus.getLen());
        for (BlockLocation blockLocation : locations){
            String[] hosts = blockLocation.getHosts();
            for (String host : hosts){
                System.out.println("block : " + blockLocation + " host : " + host);
            }
        }
    }


    /**
     * list all files and their properties under /
     * including permssions, owners, group and path
     */
    @Test
    public void iteratorListFiles() throws IOException {
        String listHdfs = "/";
        RecursionList(hdfs, new Path(listHdfs));
    }
    public void RecursionList(FileSystem hdfs, Path path) throws IOException {
        FileStatus[] files = hdfs.listStatus(path);
        for (FileStatus file : files){
            System.out.println(file.getPermission() + " " +
                    file.getOwner() + " " +
                    file.getGroup() + " " +
                    file.getPath());
            if(file.isDirectory()){
                RecursionList(hdfs, file.getPath());
            }
        }
    }

    /**
     *  list all file's properties under /hdfsTest including permissions/
     *  owner/group and path
     * @throws IOException
     */
    @Test
    public void ListFiles() throws IOException {
        String listHdfs = "/hdfsTest";
        FileStatus[] files = hdfs.listStatus(new Path(listHdfs));
        for (FileStatus file : files){
            System.out.println(file.getPermission() + " " +
                    file.getOwner() + " " +
                    file.getGroup() + " " +
                    file.getPath());
        }
    }


    /**
     * download files to local file system
     */
    @Test
    public void downloadFiled() throws IOException {
        String fromHdfs = "/hdfsTest/sample_data";
        String toLocal = "/data/out";
        hdfs.copyToLocalFile(new Path(fromHdfs), new Path(toLocal));
        System.out.println("Finish!!");
    }


    /**
     * upload files to hdfs
     * @throws IOException
     */
    @Test
    public void uploadFiles() throws IOException {
        String fromLinux = "/data/in/sample_data";
        String toHdfs = "/hdfsTest";
        hdfs.copyFromLocalFile(new Path(fromLinux), new Path(toHdfs));
        System.out.println("finish!!!");
    }


    @Test
    public void createFile() throws URISyntaxException, IOException {
        String newDir = "/hdfsTest/touchFile";
        FSDataOutputStream rst = hdfs.create(new Path(newDir));
        System.out.println("Finish!!");
    }


    @Test
    public void makeDir() throws IOException, URISyntaxException {
        String newDir = "/hdfsTest/touchFile";
        boolean rst = hdfs.mkdirs(new Path(newDir));
        if(rst){
            System.out.println("Success!");
        }else{
            System.out.println("Failed!");
        }
    }

}
