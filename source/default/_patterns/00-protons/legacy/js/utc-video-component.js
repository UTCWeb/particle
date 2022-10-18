(function($, Drupal, drupalSettings) {
    "use strict";

    Drupal.behaviors.utcvideocomponent = {
        attach: function(context, settings) {  
            var videoContainer = document.querySelector(".media-video").closest(".container");
            videoContainer.classList.add("video-container");
            var videoDivChild = document.querySelector(".video-container > div");
            videoDivChild.classList.add("video-div-child");
            videoDivChild.style.display = "block";
            var mediaVideo = document.querySelector(".media-video");
            mediaVideo.style.width = "100%";

            var test = document.getElementsByClass("media-video"),
            classes = ['banner-video'];

            test.innerHTML = "";

            for(var i = 0, j = classes.length; i < j; i++) {
                if(hasClass(test, classes[i])) {
                    test.innerHTML = "I have " + classes[i];
                    break;
                } else {
                    test.innerHTML = "I don't have " + classes[i];
                    break;
                }
            }

            let myFrame = document.querySelector(".utc-oembed iframe").src;
            myFrame = myFrame + "?autoplay=1&amp;mute=1&amp;modestbranding=1&amp;showinfo=0&amp;rel=0&amp;cc_load_policy=0&amp;iv_load_policy=0&amp;controls=0&amp;disablekb=0&amp;fs=0&amp;color=white&amp;loop=1&amp;playlist=' + youtubeID + '&amp;start=0";

        }
    };
}(jQuery, Drupal, drupalSettings));