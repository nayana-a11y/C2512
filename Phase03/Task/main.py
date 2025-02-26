import json

with open("usb_music.json", "r") as playbackfile:
    playback_data = json.load(playbackfile)

successful_tracks = {"tracks": []}
failed_tracks = {"tracks": []}

for key, value in playback_data.items():
    if isinstance(value, dict):  
        for folder, tracks in value.items():
            if isinstance(tracks, list): 
                for track in tracks:
                    if isinstance(track, dict) and track.get("playable") == "yes": 
                        track_info = {
                        "song": track.get("name"),
                        "path": track.get("containerPath"),
                        "result": "pass" if track.get("playback") == "success" else "failure"
                        }

                        if track.get("playback") == "success":
                            successful_tracks["tracks"].append(track_info)
                        elif track.get("playback") == "failure":
                            failed_tracks["tracks"].append(track_info)

with open("Successful_Tracks.json", "w") as success_file:
    json.dump(successful_tracks, success_file, indent=4)

with open("Failed_Tracks.json", "w") as fail_file:
    json.dump(failed_tracks, fail_file, indent=4)

print("Processing complete.")
 
 
