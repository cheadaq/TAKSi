# Copyright (C) 2018-present ichenq@outlook.com. All rights reserved.
# Distributed under the terms and conditions of the Apache License.
# See accompanying files LICENSE.


JAVA_CLASS_TEMPLATE = """

import java.io.*;
import java.util.*;
import java.util.function.Function;

public class %s {

    final public static String LF = "\\n"; // line feed

    // parse text to boolean value
    public static boolean parseBool(String text) {
        if (!text.isEmpty()) {
            return text.equals("1") ||
                    text.equalsIgnoreCase("on") ||
                    text.equalsIgnoreCase("yes")  ||
                    text.equalsIgnoreCase("true");
        }
        return false;
    }

    public static String readFileContent(String filepath) {
        StringBuilder sb = new StringBuilder();
        try (BufferedReader reader = new BufferedReader(new FileReader(filepath))) {
            String line = null;
            while ((line = reader.readLine()) != null) {
                sb.append(line);
                sb.append(LF); // line break
            }
        } catch(IOException ex) {
            System.err.println(ex.getMessage());
            ex.printStackTrace();
        }
        return sb.toString();
    }

    // you can set your own file content reader
    public static Function<String, String> reader;

    public static String[] readFileToTextLines(String filename) {
        if (reader == null) {
            reader = (filepath)-> readFileContent(filepath);
        }
        String content = reader.apply(filename);
        return content.split(LF, -1);
    }    

"""
