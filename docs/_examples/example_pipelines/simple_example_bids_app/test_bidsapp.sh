parent_dir="$(dirname "$(pwd)")"
docker run -v $parent_dir/example_data:/data:ro -v ~/outdocker:/out bidsapp /data /out participant --participant_label 01
