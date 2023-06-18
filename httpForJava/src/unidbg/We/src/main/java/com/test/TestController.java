package com.test;

import com.kanxue.algorithmbase.MainActivity;
import org.springframework.beans.factory.annotation.Value;
import org.springframework.web.bind.annotation.*;

import javax.validation.Valid;
import java.io.File;

import java.util.HashMap;
import java.util.Map;

@RestController
@RequestMapping("/web")
public class TestController {
    @Value("${apk.url}")
    private String url;

    @GetMapping("/getTest")
    public Map<String,Object> getTest(@RequestParam(required = false,defaultValue = "abcdef0123456789") String input) {
        File file = new File(url);
        MainActivity mainActivity = new MainActivity(file.getPath());
        String str = mainActivity.encodeByString(input);
        Map<String, Object> result = new HashMap<>();
        result.put("code", 0);
        result.put("message", "调用成功");
        result.put("data", str);
        return result;
    }


    @PostMapping("/postTest")
    public Map<String,Object>  postTest(@RequestBody Map<String,String> requestMap) {
        String input = requestMap.get("input");
        File file = new File(url);
        MainActivity mainActivity = new MainActivity(file.getPath());
        String str = mainActivity.encodeByString(input);
        Map<String, Object> result = new HashMap<>();
        result.put("code", 0);
        result.put("message", "调用成功");
        result.put("data",str);
        return result;
    }
}
